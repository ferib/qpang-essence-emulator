#ifndef INFO_MANAGER_LOBBY_HPP
#define INFO_MANAGER_LOBBY_HPP

#include <cstdint>
#include <string>
#include <array>
#include <iostream>
#include "boost/format.hpp"
#include "database.hpp"

class InfoManager {

public:
	InfoManager();
	~InfoManager();

	void Load(uint32_t userId);

	inline std::array<uint8_t, 16> Uuid() { return _uuid; };
	std::array<uint8_t, 16> Uuid(std::array<uint8_t, 16> uuid);

	inline uint32_t Id() { return _playerId; };

	inline std::string Nickname() { return _nickname; };
	std::string Nickname(std::string nickname);

	inline uint16_t Level() { return _level; };
	uint16_t Level(uint16_t level);

	inline uint32_t Experience() { return _experience; };
	uint32_t Experience(uint32_t experience);

	inline uint8_t Rank() { return _rank; };
	uint8_t Rank(uint8_t rank);

	inline uint32_t Prestige() { return _prestige; };
	uint32_t Prestige(uint32_t prestige);

	inline uint16_t Character() { return _character; };
	uint16_t Character(uint16_t character);

	inline uint32_t Don() { return _don; };
	uint32_t Don(uint32_t don);

	inline uint32_t Cash() { return _cash; };
	uint32_t Cash(uint32_t cash);

	inline uint32_t Coins() { return _coins; };
	uint32_t Coins(uint32_t coins);

	inline uint16_t Channel() { return _channelId; };
	uint16_t Channel(uint16_t channelId);

	inline uint32_t Uid() { return _uid; };
	uint32_t Uid(uint32_t uid);

private:

	void ExecuteQuery(std::string query);

	std::array<uint8_t, 16> _uuid;
	uint32_t _playerId;
	std::string _nickname = std::string();
	uint16_t _level = 1;
	uint32_t _experience = 0;
	uint8_t _rank = 1;
	uint32_t _prestige = 0;
	uint16_t _character = 333;
	uint32_t _don = 0;
	uint32_t _coins = 0;
	uint32_t _cash = 0;
	uint16_t _channelId = 0;
	uint32_t _uid;
};

#endif // !INFO_MANAGER_HPP
