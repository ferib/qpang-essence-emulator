#ifndef HANDSHAKE_RESPONSE_EVENT_HPP
#define HANDSHAKE_RESPONSE_EVENT_HPP

#include <cstdint>
#include "packet_event.hpp"

class HandshakeResponseEvent : public PacketEvent {

public:
	ServerPacket Compose(Connection::Ptr conn) override 
	{
		Packets::Handshake::KeyExchangeRsp rsp{};
		auto packet = ServerPacket::Create<Opcode::KEY_EXCHANGE_RSP, Packets::Handshake::KeyExchangeRsp>();
		rsp.WriteToArray(conn->GetAuthenticateKeyPart(), rsp.keyPart);
		packet.Write(rsp);
		return packet;
	};
};


#endif