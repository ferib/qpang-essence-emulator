#ifndef HANDSHAKE_EVENT_HPP
#define HANDSHAKE_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "handshake_response_event.hpp"

class HandshakeEvent : public LobbyPacketEvent {

public:
	HandshakeEvent() : LobbyPacketEvent(sizeof(Packets::Handshake::KeyExchange)) {};

	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto keyExchange = pack.Read<Packets::Handshake::KeyExchange>(NULL);
		session->Send(HandshakeResponseEvent{}.Compose(session), BlowfishContext::CryptoType::PUBLIC);
	}
};

#endif