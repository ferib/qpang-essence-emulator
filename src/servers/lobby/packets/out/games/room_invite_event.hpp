#ifndef ROOM_INVITE_EVENT_HPP
#define ROOM_INVITE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"

class RoomInviteEvent : public LobbyPacketEvent {

public:
	RoomInviteEvent()
	{
	}

	ServerPacket Compose(LobbySession* session) override
	{
		
	}
private:
};

#endif