#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include "database.hpp"
#include "weapon.hpp"

#include <map>
#include <cstdint>
#include <string>
#include "level.hpp"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void Load();

	Level GetLevel(uint32_t experience);

private:
	//level, Level
	std::map<uint32_t, Level> _levels;
};


#endif // !LEVEL_MANAGER_HPP