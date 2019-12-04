#ifndef OUTGOING_FRIEND_ACCEPTED_EVENT_HPP
#define OUTGOING_FRIEND_ACCEPTED_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"
#include "friend_manager.hpp"

class OutgoingFriendAcceptedEvent : public LobbyPacketEvent {

public:
	OutgoingFriendAcceptedEvent(Friend theFriend) { _friend = theFriend; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::AddIncomingFriend rsp{};
		rsp.buddy.id = _friend.toPlayerId;
		rsp.buddy.isOnline = true;
		rsp.buddy.level = _friend.level;
		wcsncpy(rsp.buddy.name, std::wstring(_friend.nickname.begin(), _friend.nickname.end()).data(), 16);
		rsp.buddy.friendState = FriendManager::FRIENDS;

		return ServerPacket::Create<Opcode::LOBBY_OUTGOING_FRIEND_ACCEPTED>(rsp);
	};
private:
	Friend _friend;
};

#endif