#ifndef SEND_MEMO_RESPONSE_EVENT_HPP
#define SEND_MEMO_RESPONSE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"

class SendMemoResponseEvent : public LobbyPacketEvent {

public:
	SendMemoResponseEvent(uint32_t memosLeft) { _memosLeft = memosLeft; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::SendMemoRsp rsp{};
		rsp.memosLeft = _memosLeft;
		return ServerPacket::Create<Opcode::LOBBY_SEND_MEMO_RSP>(rsp);
	};
private:
	uint32_t _memosLeft;
};

#endif