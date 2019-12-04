#ifndef CHARACTER_EVENT_HPP
#define CHARACTER_EVENT_HPP

#include "lobby_packet_event.hpp"
#include <cstdint>

#include "character_response_event.hpp"
#include "info_manager.hpp"
#include "lobby_session.hpp"

class CharacterEvent : public LobbyPacketEvent {

public:
	CharacterEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::CharacterChange)) {};

	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::CharacterChange>();

		if (session->Info()->Character() == packet.characterId)
			return; // not supposed to happen.

		uint16_t character = session->Info()->Character(packet.characterId);
		session->Send(CharacterResponseEvent{ character }.Compose(session));
	}
};

#endif