#ifndef HANDSHAKE_RESPONSE_EVENT_HPP
#define HANDSHAKE_RESPONSE_EVENT_HPP

#include <memory>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"

class HandshakeResponseEvent : public LobbyPacketEvent {

public:
	ServerPacket Compose(LobbySession* session) override {
		Packets::Handshake::KeyExchangeRsp rsp{};
		auto packet = ServerPacket::Create<Opcode::KEY_EXCHANGE_RSP, Packets::Handshake::KeyExchangeRsp>();
		rsp.WriteToArray(session->GetConnection()->GetAuthenticateKeyPart(), rsp.keyPart);
		packet.Write(rsp);
		return packet;
	};
};

#endif