#ifndef ROOM_RANDOM_INVITE_EVENT_HPP
#define ROOM_RANDOM_INVITE_EVENT_HPP

#include "lobby_packet_event.hpp"

class RoomRandomInviteEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto data = pack.Read<Packets::Lobby::RoomRandomInvite>();
	}
};

#endif