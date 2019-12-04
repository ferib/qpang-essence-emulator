#ifndef ADD_FRIEND_RESPONSE_EVENT_HPP
#define ADD_FRIEND_RESPONSE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "friend.hpp"
#include "friend_manager.hpp"
#include "string_converter.hpp"

class AddFriendResponseEvent : public LobbyPacketEvent {

public:
	AddFriendResponseEvent(Friend theFriend, bool isOnline, wchar_t nickname[17]) { _friend = theFriend; _isOnline = isOnline; wcscpy(_nickname, nickname); };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::AcceptFriendRequestRsp rsp{};
		
		rsp.newFriend.friendId = _friend.toPlayerId;
		wcsncpy(rsp.newFriend.friendName, std::wstring(_friend.nickname.begin(), _friend.nickname.end()).data(), 16);
		rsp.newFriend.isOnline = _isOnline;
		rsp.newFriend.friendLevel = _friend.level;
		rsp.newFriend.friendState = FriendManager::State::OUTGOING;

		return ServerPacket::Create<Opcode::LOBBY_FRIEND_INVITE_RSP>(rsp);
	};
private:
	Friend _friend;
	bool _isOnline;
	wchar_t _nickname[17];
};

#endif