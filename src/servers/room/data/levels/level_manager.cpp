#include "level_manager.hpp"

LevelManager::LevelManager()
{
	Load();
}

LevelManager::~LevelManager()
{
}

void LevelManager::Load()
{
	sLogger->Get()->info("Loading levels");

	Database database{};

	auto result = database.storeQuery("SELECT * FROM levels");

	if (result != nullptr)
	{
		do
		{
			uint32_t level = result->getNumber<uint32_t>("level");
			std::string name = result->getString("name");
			uint32_t experience = result->getNumber<uint32_t>("experience");
			uint32_t don = result->getNumber<uint32_t>("don_reward");
			uint32_t cash = result->getNumber<uint32_t>("cash_reward");
			uint32_t coin = result->getNumber<uint32_t>("coin_reward");

			_levels[level] = Level{ level, name, experience, don, cash, coin, experience };

			result->next();
		} while (result->hasNext());

		sLogger->Get()->info("Loaded {0:d} levels", _levels.size());
	}

	database.Close();
}

Level LevelManager::GetLevel(uint32_t experience)
{
	for (auto& level : _levels)
	{
		if (level.second.experience > experience)
		{
			if (level.first - 1 == NULL)
				return _levels.begin()->second;

			return _levels[level.first - 1];
		}
	}

	return _levels.end()->second;
}
