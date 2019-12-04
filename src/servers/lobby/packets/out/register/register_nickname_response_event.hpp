#ifndef REGISTER_NICKNAME_RESPONSE_EVENT_HPP
#define REGISTER_NICKNAME_RESPONSE_EVENT_HPP

#include <cstdint>
#include <string>
#include "packet_data.hpp"
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"


class RegisterNicknameResponseEvent : public LobbyPacketEvent {

public:
	RegisterNicknameResponseEvent(std::string nickname) { _nickname = nickname; };
	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::CheckNameRsp rsp{};
		wcsncpy(rsp.responseName, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);
		return ServerPacket::Create<Opcode::LOBBY_REGISTER_NAME_RSP>(rsp);
	};
private:
	std::string _nickname;
};

#endif