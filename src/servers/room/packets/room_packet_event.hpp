#ifndef ROOM_PACKET_EVENT_HPP
#define ROOM_PACKET_EVENT_HPP

#include "packet_event.hpp"

class GameLobbySession;

class RoomPacketEvent : public PacketEvent {

public:
	virtual void Read(GameLobbySession* session, ClientPacket& pack) {};
	virtual ServerPacket Compose(GameLobbySession* session) { return ServerPacket{}; };
};

#endif