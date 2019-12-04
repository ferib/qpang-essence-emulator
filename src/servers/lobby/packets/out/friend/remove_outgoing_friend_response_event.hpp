#ifndef REMOVE_OUTGOING_FRIEND_RESPONSE_EVENT_HPP
#define REMOVE_OUTGOING_FRIEND_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class RemoveOutgoingFriendResponseEvent : public LobbyPacketEvent {

public:
	RemoveOutgoingFriendResponseEvent(uint32_t targetId) { _targetId = targetId; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::RemoveOutgoingFriendRsp rsp{};
		rsp.targetId = _targetId;
		return ServerPacket::Create<Opcode::LOBBY_REMOVE_OUTGOING_FRIEND_RSP>(rsp);
	};
private:
	uint32_t _targetId;
};

#endif