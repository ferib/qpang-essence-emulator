#include "room_info_manager.hpp"
#include "game.hpp"

RoomInfoManager::RoomInfoManager()
{
}

RoomInfoManager::~RoomInfoManager()
{
}

void RoomInfoManager::Save()
{
	sLogger->Get()->debug("Saving room info for: {0}", Nickname());

	Experience(Experience() + GainedExperience());
	Don(Don() + GainedDon());
	Cash(Cash() + GainedCash());
	Coins(Coins() + GainedCoins());
	Kills(Kills() + GainedKills());
	Deaths(Deaths() + GainedDeaths());

	Level(sGame->Levels().GetLevel(Experience()).level);

	Database database{};
	database.executeQuery(str(boost::format("UPDATE players SET experience = %1%, don = %2%, cash = %3%, coins = %4%, level = %5% WHERE id = %6% ") % Experience() % Don() % Cash() % Coins() % Level() % Id()).c_str());
	database.Close();
}

uint32_t RoomInfoManager::Id(uint32_t id)
{
	return _playerId = id;
}

std::string RoomInfoManager::Nickname(std::string nickname)
{
	return _nickname = nickname;
}

uint16_t RoomInfoManager::Level(uint16_t level)
{
	return _level = level;
}

uint32_t RoomInfoManager::Experience(uint32_t experience)
{
	return _experience = experience;
}

uint32_t RoomInfoManager::GainExperience(uint32_t experience)
{
	return _gainedExperience += experience;
}

uint8_t RoomInfoManager::Rank(uint8_t rank)
{
	return _rank = rank;
}

uint32_t RoomInfoManager::Prestige(uint32_t prestige)
{
	return _prestige = prestige;
}

uint16_t RoomInfoManager::Character(uint16_t character)
{
	return _character = character;
}

uint32_t RoomInfoManager::Don(uint32_t don)
{
	return _don = don;
}

uint32_t RoomInfoManager::AddDon(uint32_t don)
{
	return _gainedDon += don;
}

uint32_t RoomInfoManager::GainedDon()
{
	return _gainedDon;
}

uint32_t RoomInfoManager::Cash(uint32_t cash)
{
	return _cash = cash;
}

uint32_t RoomInfoManager::AddCash(uint32_t cash)
{
	return _gainedCash += cash;
}

uint32_t RoomInfoManager::GainedCash()
{
	return _gainedCash;
}

uint32_t RoomInfoManager::Coins(uint32_t coins)
{
	return _coins = coins;
}

uint32_t RoomInfoManager::AddCoins(uint32_t coins)
{
	return _gainedCoins += coins;
}

uint32_t RoomInfoManager::GainedCoins()
{
	return _gainedCoins;
}

uint32_t RoomInfoManager::Health(uint32_t health)
{
	return _health = health;
}

uint32_t RoomInfoManager::SkillPoints(uint32_t skillPoints)
{
	return _skillPoints = skillPoints;
}

uint32_t RoomInfoManager::SkillGauge(uint32_t newSkillLevel)
{
	return _skillGauge = newSkillLevel;
}

uint8_t RoomInfoManager::Team(uint8_t team)
{
	return _team = team;
}

uint32_t RoomInfoManager::State(uint32_t state)
{
	return _state = state;
}

uint8_t RoomInfoManager::Ready(uint8_t value)
{
	return _ready = value;
}

uint8_t RoomInfoManager::InGame(uint8_t value)
{
	return _inGame = value;
}

uint8_t RoomInfoManager::Invincible(uint8_t invincible)
{
	return _invincible = invincible;
}

uint32_t RoomInfoManager::Kills(uint32_t kills)
{
	return _kills = kills;
}

uint32_t RoomInfoManager::AddKill()
{
	return _gainedKills++;
}

uint16_t RoomInfoManager::GainedKills()
{
	return _gainedKills;
}

uint32_t RoomInfoManager::Deaths(uint32_t deaths)
{
	return _deaths = deaths;
}

uint32_t RoomInfoManager::AddDeath()
{
	return _gainedDeaths++;
}

uint16_t RoomInfoManager::GainedDeaths()
{
	return _gainedDeaths;
}

uint8_t RoomInfoManager::IncrementKillStreak()
{
	return _killStreak++;
}

void RoomInfoManager::ResetKillStreak()
{
	_killStreak = NULL;
}

uint32_t RoomInfoManager::CurrentWeapon(uint32_t currentWeapon)
{
	return _currentWeapon = currentWeapon;
}

void RoomInfoManager::Equipment(std::array<uint32_t, 13> equipment)
{
	_items = equipment;
}

std::array<uint32_t, 9> RoomInfoManager::Armor()
{
	return
	{
		_items[0],
		_items[1],
		_items[2],
		_items[3],
		_items[4],
		_items[5],
		_items[6],
		_items[7],
		_items[8],
	};
}

std::array<uint32_t, 4> RoomInfoManager::Weapons()
{
	return
	{
		_items[9],
		_items[10],
		_items[11],
		_items[12],
	};
}

void RoomInfoManager::Reset()
{
	_skillGauge = 0;
	_killStreak = 0;
	_kills = 0;
	_deaths = 0;
	_essenceTime = 0;
	_startedAt = time(NULL);
	_gainedExperience = 0;
	_gainedDon = 0;
	_gainedCash = 0;
	_gainedCoins = 0;
	_gainedKills = 0;
	_gainedDeaths = 0;
}
