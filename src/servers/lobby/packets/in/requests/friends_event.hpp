#ifndef FRIENDS_EVENT_HPP
#define FRIENDS_EVENT_HPP

#include <memory>
#include <math.h>
#include "lobby_packet_event.hpp"
#include <vector>
#include "lobby_session.hpp"
#include "friend.hpp"
#include "friend_manager.hpp"
#include "friends_response_event.hpp"

/// TODO List packet implementation testing required!
class FriendsEvent : public LobbyPacketEvent {
private:
	const double maxFriendsPerPacket = 10;
public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::vector<Friend> allFriends = session->Friends()->List();

		uint32_t totalCount = allFriends.size();
		uint32_t countInPacket = ceil(totalCount / maxFriendsPerPacket);

		for (int i = 0; i < countInPacket; i++)
		{
			int j = i * maxFriendsPerPacket + maxFriendsPerPacket;
			uint32_t totalSent = j >= totalCount ? totalCount : j;
			std::vector<Friend> toSend(allFriends.begin() + i * maxFriendsPerPacket, allFriends.begin() + totalSent);
			session->Send(FriendsResponseEvent{ totalSent, totalCount, toSend }.Compose(session));
		}
	}
};

#endif