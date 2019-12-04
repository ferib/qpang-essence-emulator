#ifndef WHISPER_FAIL_EVENT_HPP
#define WHISPER_FAIL_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"

class WhisperFailEvent : public LobbyPacketEvent {

public:
	WhisperFailEvent(uint32_t error) { _error = error; }

	ServerPacket Compose(LobbySession* session) override 
	{
		Packets::Error rsp{};
		rsp.errorId = _error;
		return ServerPacket::Create<Opcode::LOBBY_WHISPER_FAIL>(rsp);
	};

private:
	uint32_t _error;
};

#endif