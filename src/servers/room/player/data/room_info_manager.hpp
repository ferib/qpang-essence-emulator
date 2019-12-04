#ifndef ROOM_INFO_MANAGER_HPP
#define ROOM_INFO_MANAGER_HPP

#include <cstdint>
#include <array>
#include <string>
#include <iostream>
#include "position.hpp"
#include <time.h>

class RoomInfoManager {

public:

	enum Team : uint8_t
	{
		NO_TEAM = 0,
		BLUE = 1,
		YELLOW = 2,
	};


	RoomInfoManager();
	~RoomInfoManager();

	void Load(uint32_t userId);
	void Save();

	uint32_t Id(uint32_t playerId);
	inline uint32_t Id() { return _playerId; };

	inline std::string Nickname() { return _nickname; };
	std::string Nickname(std::string nickname);

	inline uint16_t Level() { return _level; };
	uint16_t Level(uint16_t level);

	inline uint32_t Experience() { return _experience; };
	uint32_t Experience(uint32_t experience);
	inline uint32_t GainedExperience() { return _gainedExperience; };
	uint32_t GainExperience(uint32_t experience);

	inline uint8_t Rank() { return _rank; };
	uint8_t Rank(uint8_t rank);

	inline uint32_t Prestige() { return _prestige; };
	uint32_t Prestige(uint32_t prestige);

	inline uint16_t Character() { return _character; };
	uint16_t Character(uint16_t character);

	inline uint32_t Don() { return _don; };
	uint32_t Don(uint32_t don);
	uint32_t AddDon(uint32_t don);
	uint32_t GainedDon();

	inline uint32_t Cash() { return _cash; };
	uint32_t Cash(uint32_t cash);
	uint32_t AddCash(uint32_t cash);
	uint32_t GainedCash();

	inline uint32_t Coins() { return _coins; };
	uint32_t Coins(uint32_t coins);
	uint32_t AddCoins(uint32_t coins);
	uint32_t GainedCoins();

	inline uint32_t State() { return _state; };
	uint32_t State(uint32_t state);

	inline uint32_t Health() { return _health; };
	inline uint32_t StartingHealth()
	{
		// TODO bloody magic numbers... Also, map health values somewhere? and include health gained by accessories.
		switch (Character())
		{
		case 333:
		case 343:
			return 100;
		case 578:
			return 150;
		case 579:
			return 90;
		case 850:
		case 851:
			return 125;
		}

		return 0;
	}

	uint32_t Health(uint32_t health);

	inline uint32_t SkillPoints() { return _skillPoints; }
	uint32_t SkillPoints(uint32_t skillPoints);

	inline uint32_t SkillGauge() { return _skillGauge; };
	uint32_t SkillGauge(uint32_t newSkillLevel);

	inline uint8_t Team() { return _team; };
	uint8_t Team(uint8_t team);

	inline uint8_t Ready() { return _ready; };
	uint8_t Ready(uint8_t value);

	inline uint8_t InGame() { return _inGame; };
	uint8_t InGame(uint8_t value);

	inline uint8_t Invincible() { return _invincible; };
	uint8_t Invincible(uint8_t invincible);

	inline uint32_t Kills() { return _kills; };
	uint32_t Kills(uint32_t kills);
	uint32_t AddKill();
	uint16_t GainedKills();

	inline uint32_t Deaths() { return _deaths; };
	uint32_t Deaths(uint32_t deaths);
	uint32_t AddDeath();
	uint16_t GainedDeaths();

	inline uint32_t CurrentWeapon() { return _currentWeapon; };
	uint32_t CurrentWeapon(uint32_t currentWeapon);

	inline uint8_t KillStreak() { return _killStreak; };
	uint8_t IncrementKillStreak();
	void ResetKillStreak();

	inline time_t StartedAt() { return _startedAt; };

	void Equipment(std::array<uint32_t, 13> equipment);

	inline bool Alive() { return _health > 0; };

	std::array<uint32_t, 9> Armor();
	std::array<uint32_t, 4> Weapons();

	void Reset();
private:

	uint32_t _playerId = 0;
	std::string _nickname = std::string();
	uint16_t _level = 1;
	uint32_t _experience = 0;
	uint32_t _gainedExperience = 0;
	uint32_t _gainedDon = 0;
	uint32_t _gainedCash = 0;
	uint32_t _gainedCoins = 0;
	uint32_t _gainedDeaths = 0;
	uint32_t _gainedKills = 0;
	uint8_t _rank = 1;
	uint32_t _prestige = 0;
	uint16_t _character = 333;
	uint32_t _don = 0;
	uint32_t _coins = 0;
	uint32_t _cash = 0;
	uint32_t _state = 0;
	uint32_t _health = 0;
	uint32_t _skillPoints = 0;
	uint32_t _skillGauge = 0;
	uint8_t _team = Team::BLUE;
	uint8_t _ready = false;
	uint8_t _inGame = false;
	uint8_t _invincible = false;
	uint8_t _killStreak = 0;
	uint32_t _kills = 0;
	uint32_t _deaths = 0;
	uint16_t _essenceTime = 0;
	uint32_t _currentWeapon = 0;
	Position _position{};

	time_t _startedAt = time(NULL);

	std::array<uint32_t, 13> _items = {};
};

#endif // !INFO_MANAGER_HPP
