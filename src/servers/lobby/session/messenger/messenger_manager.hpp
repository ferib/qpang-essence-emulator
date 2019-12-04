#ifndef MESSENGER_MANAGER_HPP
#define MESSENGER_MANAGER_HPP

#define MAX_MESSAGES 19

#include <string>
#include <cstdint>
#include <vector>
#include <time.h>
#include <boost/format.hpp>
#include "database.hpp"
#include "message.hpp"

class MessengerManager {
public:
	void Load(uint32_t playerId);
	Message ReceiveMemo(uint32_t fromId, uint32_t targetId, std::string nickname, std::string message);
	void AddMemo(Message message);
	void OpenMemo(uint32_t memoId);
	bool RemoveMemo(uint32_t memoId);
	std::vector<Message> List();
private:
	std::vector<Message> _messages;
};

#endif // !MESSENGER_MANAGER_HPP
