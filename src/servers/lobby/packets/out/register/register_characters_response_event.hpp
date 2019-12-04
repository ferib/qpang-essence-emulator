#ifndef REGISTER_CHARACTERS_RESPONSE_EVENT_HPP
#define REGISTER_CHARACTERS_RESPONSE_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"
#include <string>

class RegisterCharactersResponseEvent : public LobbyPacketEvent {

public:
	RegisterCharactersResponseEvent(std::string nickname, uint16_t character1, uint16_t character2) { _nickname = nickname; _character1 = character1; _character2 = character2; };
	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::RegisterFinishRsp rsp{};
		rsp.character1 = rsp.defaultCharacter = _character1;
		rsp.character2 = _character2;
		wcsncpy(rsp.responseName, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);
		return ServerPacket::Create<Opcode::LOBBY_REGISTER_CHARACTERS_RSP>(rsp);
	};
private:
	std::string _nickname;
	uint16_t _character1;
	uint16_t _character2;
};

#endif