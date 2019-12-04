#ifndef ADD_INCOMING_FRIEND_EVENT_HPP
#define ADD_INCOMING_FRIEND_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"

class AddIncomingFriendEvent : public LobbyPacketEvent {

public:
	AddIncomingFriendEvent(Friend theFriend) { _friend = theFriend; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::AddIncomingFriend rsp{};
		rsp.buddy.id = _friend.toPlayerId;
		rsp.buddy.level = _friend.level;
		rsp.buddy.friendState = FriendManager::State::INCOMING;
		wcsncpy(rsp.buddy.name, std::wstring(_friend.nickname.begin(), _friend.nickname.end()).data(), 16);
		rsp.buddy.isOnline = true;

		return ServerPacket::Create<Opcode::LOBBY_ADD_INCOMING_FRIEND>(rsp);
	};
private:
	Friend _friend;
};

#endif