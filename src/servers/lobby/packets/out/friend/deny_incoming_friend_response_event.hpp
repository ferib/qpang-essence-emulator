#ifndef DENY_INCOMING_FRIEND_RESPONSE_EVENT_HPP
#define DENY_INCOMING_FRIEND_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"

class DenyIncomingFriendResponseEvent : public LobbyPacketEvent {

public:
	DenyIncomingFriendResponseEvent(uint32_t playerId) { _playerId = playerId; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::DenyFriendRequestTargetRsp rsp{};
		rsp.pendingFriendId = _playerId;
		return ServerPacket::Create<Opcode::LOBBY_DENY_INCOMING_FRIEND_RSP>(rsp);
	};
private:
	uint32_t _playerId;
};

#endif