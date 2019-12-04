#ifndef LOBBY_PACKET_EVENT_HPP
#define LOBBY_PACKET_EVENT_HPP

#include <memory>
#include "packet_event.hpp"

//fwd
class LobbySession;

class LobbyPacketEvent : public PacketEvent {

public:
	LobbyPacketEvent(uint32_t packetSize) : PacketEvent(packetSize) {};
	LobbyPacketEvent() : PacketEvent(0) {};
	virtual void Read(LobbySession* session, ClientPacket& pack) {};
	virtual ServerPacket Compose(LobbySession* session) { return ServerPacket{}; };
};

#endif