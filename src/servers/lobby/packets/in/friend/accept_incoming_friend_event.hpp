#ifndef ACCEPT_INCOMING_FRIEND_EVENT_HPP
#define ACCEPT_INCOMING_FRIEND_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "accept_incoming_friend_response_event.hpp"
#include "friend_manager.hpp"
#include "friend.hpp"
#include "outgoing_friend_accepted_event.hpp"
#include "lobby.hpp"

class AcceptIncomingFriendEvent : public LobbyPacketEvent {

public:
	AcceptIncomingFriendEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::AcceptFriendRequest)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::AcceptFriendRequest>();

		if (!session->Friends()->HasFriend(packet.newFriendId))
			return;

		Friend theNewFriend = session->Friends()->AcceptFriend(packet.newFriendId);
		auto target = session->GetLobby()->FindSession(packet.newFriendId);

		if (target != nullptr)
		{
			Friend acceptedFriend = target->Friends()->AcceptFriend(session->Info()->Id());
			target->Send(OutgoingFriendAcceptedEvent{ acceptedFriend }.Compose(nullptr));
		}
		session->Send(AcceptIncomingFriendResponseEvent{ theNewFriend, target != nullptr }.Compose(session));
	}
};

#endif