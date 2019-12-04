#ifndef REMOVE_MEMO_RESPONSE_EVENT_HPP
#define REMOVE_MEMO_RESPONSE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"

class RemoveMemoResponseEvent : public LobbyPacketEvent {

public:
	RemoveMemoResponseEvent(uint64_t memoId) { _memoId = memoId; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::DeleteMemoRsp rsp{};
		rsp.memoId = _memoId;
		return ServerPacket::Create<Opcode::LOBBY_DELETE_MEMO_RSP>(rsp);
	};
private:
	uint64_t _memoId;
};

#endif