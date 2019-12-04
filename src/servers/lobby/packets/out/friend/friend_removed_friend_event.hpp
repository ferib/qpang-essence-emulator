#ifndef FRIEND_REMOVED_FRIEND_EVENT_HPP
#define FRIEND_REMOVED_FRIEND_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include <cstdint>
#include "string_converter.hpp"

class FriendRemovedFriendEvent : public LobbyPacketEvent {

public:
	FriendRemovedFriendEvent(uint32_t targetId, std::string nickname) { _targetId = targetId; _nickname = nickname; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::RemoveIncomingFriend rsp{};

		rsp.playerId = _targetId;
		wcsncpy(rsp.nickname, std::wstring(_nickname.begin(), _nickname.end()).data(), 16);

		return ServerPacket::Create<Opcode::LOBBY_FRIEND_REMOVE_FRIEND>(rsp);
	};
private:
	uint32_t _targetId;
	std::string _nickname;
};

#endif