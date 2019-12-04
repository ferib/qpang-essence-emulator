#ifndef FRIEND_MANAGER_HPP
#define FRIEND_MANAGER_HPP

#define MAX_FRIENDS 10

#include <memory>
#include <cstdint>
#include <vector>
#include <string>
#include "friend.hpp"
#include <boost/format.hpp>
#include "string_converter.hpp"
#include "packet.hpp"
#include "lobby.hpp"

class FriendManager {

public:

	enum State {
		FRIENDS = 1,
		OUTGOING = 2,
		INCOMING = 4,
		BOTH,
	};

	void Load(uint32_t playerId);
	std::vector<Friend> List();
	Friend ConstructFriend(uint32_t fromId, uint32_t friendPlayerId, std::string nickname, uint8_t level);
	bool HasFriend(uint32_t playerId);
	bool HasFriend(std::string username);
	bool AddFriend(Friend friendToAdd, State state);
	Friend AcceptFriend(uint32_t friendId);
	bool RemoveFriend(uint32_t targetId);
	void SendPacket(ServerPacket& pack, std::shared_ptr<Lobby> lobby);
private:
	std::vector<Friend> _friends;
};

#endif // !FRIEND_MANAGER_HPP
