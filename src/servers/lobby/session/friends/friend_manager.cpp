#include "friend_manager.hpp"

void FriendManager::Load(uint32_t playerId)
{
	sLogger->Get()->debug("Loading friends for player id: {0:d}", playerId);

	Database database{};
	std::string query = "SELECT * FROM friends JOIN players ON players.id = friends.player_to WHERE friends.player_from = %1%";
	auto result = database.storeQuery(str(boost::format(query) % playerId));

	if (result)
	{
		do
		{
			uint32_t id = result->getNumber<uint32_t>("id");
			uint32_t fromPlayerId = result->getNumber<uint32_t>("user_from");
			uint32_t toPlayerId = result->getNumber<uint32_t>("user_to");
			std::string fromPlayerNickname = result->getString("name");
			uint8_t level = result->getNumber<uint32_t>("level");
			uint8_t friendshipState = result->getNumber<uint32_t>("status");

			_friends.push_back(Friend{id, fromPlayerId, toPlayerId, fromPlayerNickname, level, friendshipState});
			result->next();

			if (_friends.size() >= 20)
				break;
		} while (result->hasNext());
	}
	database.Close();
}

std::vector<Friend> FriendManager::List()
{
	return _friends;
}

Friend FriendManager::ConstructFriend(uint32_t fromId, uint32_t friendPlayerId, std::string nickname, uint8_t level)
{
	return Friend{ 0, fromId, friendPlayerId, nickname, level, 0 };
}

bool FriendManager::HasFriend(uint32_t playerId)
{
	for (Friend theFriend : _friends)
		if (theFriend.toPlayerId == playerId)
			return true;

	return false;
}

bool FriendManager::HasFriend(std::string username)
{
	for (Friend theFriend : _friends)
		if (StringConverter::ToLowerCase(theFriend.nickname) == StringConverter::ToLowerCase(username))
			return true;

	return false;
}

bool FriendManager::AddFriend(Friend friendToAdd, State state)
{
	sLogger->Get()->debug("Adding friend: {0:d}", friendToAdd.id);

	if (HasFriend(friendToAdd.nickname))
		return false;

	if (_friends.size() >= MAX_FRIENDS)
		return false;

	Database database{};
	bool result;

	//TODO: Put this somewhere else?
	if (state != State::BOTH)
	{
		friendToAdd.state = static_cast<uint8_t>(state);
		result = database.executeQuery(str(boost::format("INSERT INTO friends (user_from, user_to, status) VALUES (%1%, %2%, %3%)") % friendToAdd.fromId % friendToAdd.toPlayerId % state));
	}
	else
	{
		result = database.executeQuery(str(boost::format("INSERT INTO friends (user_from, user_to, status) VALUES (%1%, %2%, %3%)") % friendToAdd.fromId % friendToAdd.toPlayerId % State::OUTGOING));
		database.executeQuery(str(boost::format("INSERT INTO friends (user_from, user_to, status) VALUES (%1%, %2%, %3%)") % friendToAdd.toPlayerId % friendToAdd.fromId % State::INCOMING));
		friendToAdd.state = static_cast<uint8_t>(State::OUTGOING);
	}

	database.Close();

	if(result)
		_friends.push_back(friendToAdd);

	return result;
}

Friend FriendManager::AcceptFriend(uint32_t friendId)
{
	sLogger->Get()->debug("Accepting friend, friend id: {0:d}", friendId);
	if (HasFriend(friendId))
	{
		for (auto it = _friends.begin(); it != _friends.end(); it++)
		{
			if (it->toPlayerId == friendId)
			{
				Database database{};
				database.executeQuery(str(boost::format("UPDATE friends SET status = 1 WHERE (user_from = %1% AND user_to = %2% ) OR (user_from = %2% AND user_to = %1% )") % it->toPlayerId % it->fromId));
				database.Close();
				it->state = State::FRIENDS;
				return *it;
			}
		}
	}
}

bool FriendManager::RemoveFriend(uint32_t targetId)
{
	sLogger->Get()->debug("Removing friend, player id: {0:d}", targetId);
	if (HasFriend(targetId))
	{
		for (auto it = _friends.begin(); it != _friends.end(); it++)
		{
			if (it->toPlayerId == targetId)
			{
				Database database{};
				bool result = database.executeQuery(str(boost::format("DELETE FROM friends WHERE (user_from = %1% AND user_to = %2%) OR (user_from = %2% AND user_to = %1%)") % it->toPlayerId % it->fromId));
				database.Close();
				_friends.erase(it);
				return result;
			}
		}
	}
	return false;
}

void FriendManager::SendPacket(ServerPacket& pack, std::shared_ptr<Lobby> lobby)
{
	for (Friend theFriend : _friends)
	{
		lobby->SendPacket(pack, theFriend.id);
	}
}
