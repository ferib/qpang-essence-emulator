#ifndef ACCEPT_INCOMING_FRIEND_RESPONSE_EVENT_HPP
#define ACCEPT_INCOMING_FRIEND_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"

class AcceptIncomingFriendResponseEvent : public LobbyPacketEvent {

public:
	AcceptIncomingFriendResponseEvent(Friend theFriend, bool isOnline) { _friend = theFriend; _isOnline = isOnline; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::AcceptFriendRequestRsp rsp{};
		rsp.newFriend.friendId = _friend.toPlayerId;
		rsp.newFriend.friendLevel = _friend.level;
		rsp.newFriend.friendState = _friend.state;
		rsp.newFriend.isOnline = _isOnline;
		wcsncpy(rsp.newFriend.friendName, std::wstring(_friend.nickname.begin(), _friend.nickname.end()).data(), 16);
		return ServerPacket::Create<Opcode::LOBBY_ACCEPT_INCOMING_FRIEND_RSP>(rsp);
	};
private:
	Friend _friend;
	bool _isOnline;
};

#endif