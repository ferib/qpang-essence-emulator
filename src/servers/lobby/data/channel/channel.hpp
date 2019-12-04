#ifndef _CHANNEL_H
#define _CHANNEL_H

#include <cstdint>
#include <string>

#if __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <Windows.h>
#endif

struct Channel
{
	Channel() {};
	Channel(std::string name, uint8_t minLevel, uint8_t maxLevel, uint8_t minRank, uint16_t currPlayers, uint16_t maxPlayers, std::string ipAddress)
	{
		this->name = name;
		this->minLevel = minLevel;
		this->maxLevel = maxLevel;
		this->minRank = minRank;
		this->currPlayers = currPlayers =  0;
		this->maxPlayers = maxPlayers;
		this->ipAddress = inet_addr(ipAddress.c_str());
	}

	std::string name;
	uint8_t minLevel;
	uint8_t maxLevel;
	uint8_t minRank;
	uint16_t currPlayers = 0;
	uint16_t maxPlayers;
	uint32_t ipAddress;
};

#endif //_SQUARE_H