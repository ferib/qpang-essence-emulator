#ifndef PACKET_EVENT_HPP
#define PACKET_EVENT_HPP

#include "connection.hpp"
#include "packet_data.hpp"

//fwd
class ClientPacket;

class PacketEvent {
public:

	PacketEvent(int32_t packetSize) { size = packetSize; };
	PacketEvent() { size = 0; };

	virtual void Read(Connection::Ptr conn, ClientPacket& pack) {};
	virtual ServerPacket Compose(Connection::Ptr conn) { return ServerPacket{}; };
	int32_t size;
private:
};

#endif