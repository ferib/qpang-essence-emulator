#ifndef REMOVE_FRIEND_RESPONSE_EVENT_HPP
#define REMOVE_FRIEND_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class RemoveFriendResponseEvent : public LobbyPacketEvent {

public:
	RemoveFriendResponseEvent(uint32_t targetId) { _targetId = targetId; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::RemoveFriendRsp rsp{};
		rsp.removedFriendId = _targetId;
		return ServerPacket::Create<Opcode::LOBBY_REMOVE_FRIEND_RSP>(rsp);
	};
private:
	uint32_t _targetId;
};

#endif