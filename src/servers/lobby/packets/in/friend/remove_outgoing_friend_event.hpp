#ifndef REMOVE_OUTGOING_FRIEND_EVENT_HPP
#define REMOVE_OUTGOING_FRIEND_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "remove_outgoing_friend_response_event.hpp"
#include "remove_incoming_friend_event.hpp"
#include "friend_manager.hpp"

class RemoveOutgoingFriendEvent : public LobbyPacketEvent {

public:
	RemoveOutgoingFriendEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::RemoveOutgoingFriend)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::RemoveOutgoingFriend>();

		if (session->Info()->Id() == packet.targetId)
			return;

		session->Friends()->RemoveFriend(packet.targetId);

		auto target = session->GetLobby()->FindSession(packet.targetId);

		if (target != nullptr)
		{
			target->Friends()->RemoveFriend(session->Info()->Id());
			target->Send(RemoveIncomingFriendEvent{ session->Info()->Id(), session->Info()->Nickname() }.Compose(nullptr));
		}

		session->Send(RemoveOutgoingFriendResponseEvent{ packet.targetId }.Compose(session));
	}
};

#endif