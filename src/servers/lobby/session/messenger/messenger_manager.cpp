#include "messenger_manager.hpp"

void MessengerManager::Load(uint32_t playerId)
{
	sLogger->Get()->debug("Loading messages for player id {0:d}", playerId);

	Database database{};
	std::string query = "SELECT memos.id, memos.sender_id, memos.message, players.name, memos.opened, memos.created FROM memos JOIN players ON players.id = memos.sender_id WHERE receiver_id = %1%";
	auto result = database.storeQuery(str(boost::format(query) % playerId));

	if (result)
	{
		do
		{
			uint32_t id = result->getNumber<uint32_t>("id");
			uint32_t senderId = result->getNumber<uint32_t>("sender_id");
			std::string senderName = result->getString("name");
			std::string message = result->getString("message");
			uint32_t created = result->getNumber<uint32_t>("created");
			uint8_t opened = result->getNumber<uint32_t>("opened");

			_messages.push_back(Message{id, senderId, senderName, message, created, opened});
			result->next();

			if (_messages.size() >= 20)
				break;
		} while (result->hasNext());
	}
	database.Close();
}

Message MessengerManager::ReceiveMemo(uint32_t fromId, uint32_t targetId, std::string nickname , std::string message)
{
	sLogger->Get()->debug("Memo received from: {0:d} to: {1:d}. {2}: {3}", fromId, targetId, nickname, message);
	Database database{};
	message = database.escapeString(message);

	std::string query = str(boost::format("INSERT INTO memos (sender_id, receiver_id, message, created, opened) VALUES (%1%, %2%, %3%, %4%, %5%)")
	% fromId % targetId % message % time(NULL) % 0 );
	bool result = database.executeQuery(query);
	if (result)
	{
		Message newMessage{ static_cast<uint32_t>(database.getLastInsertId()), fromId, nickname, message, static_cast<uint32_t>(time(NULL)), 0 };
		newMessage.id = database.getLastInsertId();
		newMessage.senderId = fromId;
		AddMemo(newMessage);
		database.Close();
		return newMessage;
	}
	database.Close();
	return Message{};
}

void MessengerManager::AddMemo(Message message)
{
	if (_messages.size() < 20)
		_messages.push_back(message);
}

void MessengerManager::OpenMemo(uint32_t memoId)
{
	sLogger->Get()->debug("Opening memo: {0:d}", memoId);
	for (auto it = _messages.begin(); it != _messages.end(); it++)
	{
		if (it->id == memoId)
		{
			it->opened = true;
			Database database{};
			database.executeQuery(str(boost::format("UPDATE memos SET opened = 1 WHERE id = %1%") % it->id));
			database.Close();
			return;
		}
	}
}

bool MessengerManager::RemoveMemo(uint32_t memoId)
{
	for (auto it = _messages.begin(); it != _messages.end(); it++)
	{
		if (it->id == memoId)
		{
			Database database{};
			database.executeQuery(str(boost::format("DELETE FROM memos WHERE id = %1%") % it->id));
			database.Close();
			_messages.erase(it);
			return true;
		}
	}
	return false;
}

std::vector<Message> MessengerManager::List()
{
	return _messages;
}
