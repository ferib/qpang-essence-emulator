#ifndef CHARACTER_RESPONSE_EVENT_HPP
#define CHARACTER_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>


class CharacterResponseEvent : public LobbyPacketEvent {

public:
	CharacterResponseEvent(uint16_t characterOffset) { _characterOffset = characterOffset; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::CharacterChangeRsp rsp{};

		rsp.characterId = _characterOffset;
		return ServerPacket::Create<Opcode::LOBBY_SWAP_CHARACTER_RSP>(rsp);
	};
private:
	uint16_t _characterOffset;
};

#endif