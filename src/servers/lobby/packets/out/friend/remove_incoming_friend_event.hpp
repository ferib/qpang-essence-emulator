#ifndef REMOVE_INCOMING_FRIEND_EVENT_HPP
#define REMOVE_INCOMING_FRIEND_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include <cstdint>
#include "string_converter.hpp"

class RemoveIncomingFriendEvent : public LobbyPacketEvent {

public:
	RemoveIncomingFriendEvent(uint32_t targetId, std::string nickname) { _targetId = targetId; _nickname = nickname; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::RemoveIncomingFriend rsp{};

		rsp.playerId = _targetId;
		wcsncpy(rsp.nickname, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);

		return ServerPacket::Create<Opcode::LOBBY_REMOVE_INCOMING_FRIEND>(rsp);
	};
private:
	uint32_t _targetId;
	std::string _nickname;
};

#endif