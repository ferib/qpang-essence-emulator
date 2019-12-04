#include "crane_manager.hpp"
#include <string>
#include "database.hpp"
#include "logger.hpp"

CraneManager::CraneManager()
{
	Load();
}

CraneManager::~CraneManager()
{
}

void CraneManager::Load()
{
	_items.clear();
	Database database{};

	auto result = database.storeQuery("SELECT *  FROM crane_items");
	if (result != nullptr)
	{
		sLogger->Get()->info("Loading crane items");
		do
		{
			uint32_t id = result->getNumber<uint32_t>("id");
			uint32_t itemId = result->getNumber<uint32_t>("item_id");
			uint8_t itemType = result->getNumber<uint32_t>("item_type");
			uint32_t period = result->getNumber<uint32_t>("period");
			uint8_t periodType = result->getNumber<uint32_t>("use_up");
			_items.push_back(CraneItem{ id, itemId, period, periodType, itemType });
			result->next();
		} while (result->hasNext());
	}

	sLogger->Get()->info("Loaded {0:d} items", _items.size());
	database.Close();
}

CraneItem CraneManager::Use()
{
	if (!_items.size())
		return CraneItem{ 0,0,0,0,0 };

	return _items.at(rand() % (_items.size()));
}
