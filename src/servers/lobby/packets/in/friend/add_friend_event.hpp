#ifndef ADD_FRIEND_EVENT_HPP
#define ADD_FRIEND_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "handshake_response_event.hpp"
#include "string_converter.hpp"
#include "lobby.hpp"
#include "friend_manager.hpp"
#include "friend.hpp"
#include "offline_player.hpp"
#include "add_friend_response_event.hpp"
#include "friends_response_event.hpp"
#include "add_incoming_friend_event.hpp"
#include <vector>

class AddFriendEvent : public LobbyPacketEvent {

	enum Error {
		ADD_FAIL_PEER_NOT_ALLOW = 721,
		ADD_FAIL_CANNOTFIND_USER = 804,
		ALREADY_BUDDY_REGISTERD = 832,
		NOMORE_BUDDY_PENDINGS = 854,
	};

public:
	AddFriendEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::FriendRequest)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::FriendRequest>();
		std::string targetNickname = StringConverter::WcharToString(packet.username, 16);
		bool validName = session->GetLobby()->ValidateNickname(targetNickname);

		if(session->Friends()->List().size() >= MAX_FRIENDS)
			return session->SendError<Opcode::LOBBY_FRIEND_INVITE_FAIL>(Error::NOMORE_BUDDY_PENDINGS);

		if (!validName)
			return session->SendError<Opcode::LOBBY_FRIEND_INVITE_FAIL>(Error::ADD_FAIL_CANNOTFIND_USER);

		auto target = session->GetLobby()->FindSession(targetNickname);

		if (target != nullptr)
		{
			if(target->Friends()->List().size() >= MAX_FRIENDS)
				return session->SendError<Opcode::LOBBY_FRIEND_INVITE_FAIL>(Error::NOMORE_BUDDY_PENDINGS);

			if (session->Friends()->HasFriend(targetNickname) || target->Friends()->HasFriend(session->Info()->Nickname()))
				return session->SendError<Opcode::LOBBY_FRIEND_INVITE_FAIL>(Error::ALREADY_BUDDY_REGISTERD);

			Friend targetFriend = session->Friends()->ConstructFriend(session->Info()->Id(), target->Info()->Id(), target->Info()->Nickname(), target->Info()->Level());
			bool sendSuccesful = session->Friends()->AddFriend(targetFriend, FriendManager::State::OUTGOING);

			Friend sessionFriend = target->Friends()->ConstructFriend(target->Info()->Id(), session->Info()->Id(), session->Info()->Nickname(), session->Info()->Level());
			bool receivedSuccesful = target->Friends()->AddFriend(sessionFriend, FriendManager::State::INCOMING);

			if (sendSuccesful)
			{
				session->Send(AddFriendResponseEvent{ targetFriend, true, packet.username}.Compose(session));
				target->Send(AddIncomingFriendEvent{sessionFriend}.Compose(session));
			}
		}
		else
		{
			if (session->Friends()->HasFriend(targetNickname))
				return session->SendError<Opcode::LOBBY_FRIEND_INVITE_FAIL>(Error::ADD_FAIL_PEER_NOT_ALLOW);

			OfflinePlayer offlinePlayer = session->GetLobby()->GetOfflinePlayer(targetNickname, OfflinePlayer::Type::MINIMAL);
			Friend friendToAdd = session->Friends()->ConstructFriend(session->Info()->Id(), offlinePlayer.playerId, offlinePlayer.nickname, offlinePlayer.level);

			Database database{};
			auto queryResult = database.storeQuery(str(boost::format("SELECT count(*) as count FROM friends WHERE user_to = %1%") % offlinePlayer.playerId));
			uint32_t count = queryResult->getNumber<uint32_t>("count");
			database.Close();

			if(count >= MAX_FRIENDS)
				return session->SendError<Opcode::LOBBY_FRIEND_INVITE_FAIL>(Error::NOMORE_BUDDY_PENDINGS);

			bool result = session->Friends()->AddFriend(friendToAdd, FriendManager::State::BOTH);
			if (result)
				session->Send(AddFriendResponseEvent{ friendToAdd, false, packet.username }.Compose(session));
			else
				return session->SendError<Opcode::LOBBY_FRIEND_INVITE_FAIL>(Error::NOMORE_BUDDY_PENDINGS);
		}
	}
};

#endif