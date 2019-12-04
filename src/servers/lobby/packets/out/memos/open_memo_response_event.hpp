#ifndef OPEN_MEMO_RESPONSE_EVENT_HPP
#define OPEN_MEMO_RESPONSE_EVENT_HPP

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"

class OpenMemoResponseEvent : public LobbyPacketEvent {

public:
	OpenMemoResponseEvent(uint32_t memoId) { _memoId = memoId; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::ReadMemoRsp rsp{};
		rsp.memoId = _memoId;
		return ServerPacket::Create<Opcode::LOBBY_OPEN_MEMO_RSP>(rsp);
	};
private:
	uint32_t _memoId;
};

#endif