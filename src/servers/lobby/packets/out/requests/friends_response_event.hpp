#ifndef FRIEND_RESPONSE_EVENT_HPP
#define FRIEND_RESPONSE_EVENT_HPP

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "friend.hpp"
#include "string_converter.hpp"
#include "lobby.hpp"
#include "lobby_session.hpp"

class FriendsResponseEvent : public LobbyPacketEvent {

public:
	FriendsResponseEvent(uint32_t totalSent, uint32_t totalCount, std::vector<Friend> friends) { _totalSent = totalSent, _totalCount = totalCount, _friends = friends; };

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::BuddiesRequestRsp rsp{};
		rsp.totalSent = _totalSent;
		rsp.totalCount = _totalCount;
		rsp.countInPacket = _friends.size();

		for (size_t i = 0; i < _friends.size(); i++)
		{
			Packets::Lobby::BuddiesRequestRsp::Buddy buddy;
			Friend theFriend = _friends.at(i);
			buddy.isOnline = session->GetLobby()->IsOnline(theFriend.id);
			buddy.friendState = theFriend.state;
			buddy.id = theFriend.toPlayerId;
			buddy.level = theFriend.level;
			wcsncpy(buddy.name, std::wstring(theFriend.nickname.begin(), theFriend.nickname.end()).data(), 16);
			rsp.buddies[i] = buddy;
		}

		return ServerPacket::Create<Opcode::LOBBY_BUDDIES_RSP>(rsp);
	}

private:
	uint32_t _totalSent;
	uint32_t _totalCount;
	std::vector<Friend> _friends;
};

#endif