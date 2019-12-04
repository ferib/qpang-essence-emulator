#ifndef _SQUARE_MANAGER_HPP
#define _SQUARE_MANAGER_HPP

#include <cstdint>
#include <vector>
#include "channel.hpp"
#include "database.hpp"
#include "logger.hpp"

class ChannelManager
{

public:
	ChannelManager();
	~ChannelManager();

	Channel* GetChannel(uint32_t channelIndex);
	bool AddPopulation(uint32_t channelIndex);
	void RemovePopulation(uint32_t channelIndex);
	std::vector<Channel> List();

private:
	void Load();

	const uint8_t _maxChannels = 10;
	std::vector<Channel> _channels;
	Logger* _logger;
};

#endif //_LOBBY_SERVER_H