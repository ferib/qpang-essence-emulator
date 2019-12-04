#ifndef HANDSHAKE_EVENT_HPP
#define HANDSHAKE_EVENT_HPP

#include "packet_event.hpp"
#include "packet_data.hpp"
#include "handshake_response_event.hpp"

class HandshakeEvent : public PacketEvent {


public:
	HandshakeEvent() : PacketEvent(sizeof(Packets::Handshake::KeyExchange)) {};
	void Read(Connection::Ptr conn, ClientPacket& pack) override
	{
		auto keyExchange = pack.Read<Packets::Handshake::KeyExchange>(NULL);
		auto respEvent = HandshakeResponseEvent{}.Compose(conn);
		conn->SendPacket(respEvent, BlowfishContext::CryptoType::PUBLIC);
	}
};

#endif