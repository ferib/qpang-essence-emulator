#ifndef WHISPER_RESPONSE_EVENT_HPP
#define WHISPER_RESPONSE_EVENT_HPP

#include <memory>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"
#include <vector>
#include <cstdint>
#include <string>

class WhisperResponseEvent : public LobbyPacketEvent {

public:
	WhisperResponseEvent(std::string nickname, std::string message) { _nickname = nickname; _message = message; }

	ServerPacket Compose(LobbySession* session) override 
	{
		Packets::Lobby::WhisperRsp rsp{};
		wcsncpy(rsp.nickname, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);
		wcsncpy(rsp.message, std::wstring(_message.begin(), _message.end()).data(), 254);
		return ServerPacket::Create<Opcode::LOBBY_WHISPER_RSP>(rsp);
	};

private:
	std::string _nickname;
	std::string _message;	
};

#endif