#ifndef OUTGOING_FRIEND_DENIED_EVENT_HPP
#define OUTGOING_FRIEND_DENIED_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"
#include "friend_manager.hpp"

class OutgoingFriendDeniedEvent : public LobbyPacketEvent {

public:
	OutgoingFriendDeniedEvent(uint32_t playerId, std::string nickname) { _playerId = playerId; _nickname = nickname; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::DenyFriendRequestTargetRsp rsp{};
		rsp.pendingFriendId = _playerId;
		wcsncpy(rsp.nickname, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);
		return ServerPacket::Create<Opcode::LOBBY_OUTGOING_FRIEND_DENIED>(rsp);
	};
private:
	uint32_t _playerId;
	std::string _nickname;
};

#endif