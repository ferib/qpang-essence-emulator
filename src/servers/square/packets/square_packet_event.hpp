#ifndef SQUARE_PACKET_EVENT_HPP
#define SQUARE_PACKET_EVENT_HPP

#include <memory>
#include "packet_event.hpp"

class SquareSession;

class SquarePacketEvent : public PacketEvent {

public:
	SquarePacketEvent(uint32_t size) : PacketEvent(size) {};
	SquarePacketEvent() : PacketEvent(0) {};
	virtual void Read(SquareSession* session, ClientPacket& pack) {};
	virtual ServerPacket Compose(SquareSession* session) { return ServerPacket{}; };
};

#endif