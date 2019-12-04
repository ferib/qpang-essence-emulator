#include "skill_manager.hpp"

SkillManager::SkillManager()
{
	Load();
}

SkillManager::~SkillManager(){}

void SkillManager::Load()
{
	_skills.clear();
	//Database database{};
	//auto result = database.storeQuery("SELECT * FROM skill_cards");
	//
	//if(result != nullptr)
	//{
	//	do
	//	{
	//		std::string name = result->getString("name");
	//		uint32_t itemId = result->getNumber<uint32_t>("item_id");
	//		uint16_t pointCost = result->getNumber<uint32_t>("point_cost");
	//		uint16_t duration = result->getNumber<uint32_t>("duration");
	//		_skills[itemId] = Skill { name, itemId, pointCost, duration };
	//		result->next();
	//	}
	//	while (result->hasNext());
	//}
	//
	//database.Close();
}

Skill SkillManager::GetSkill(uint32_t itemId)
{
	return _skills[itemId];
}

std::string SkillManager::GetName(uint32_t itemId)
{
	return GetSkill(itemId).name;
}

uint32_t SkillManager::GetPointCost(uint32_t itemId)
{
	return GetSkill(itemId).pointCost;
}

uint32_t SkillManager::GetDuration(uint32_t itemId)
{
	return GetSkill(itemId).duration;
}

uint32_t SkillManager::GetRandomSkillId()
{
	if (!_skills.empty())
	{
		int random = rand() % _skills.size();
		int index = 0;

		for (auto it = _skills.begin(); it != _skills.end(); it++)
			if (index++ == random)
				return it->first;
	}

	return 0;
}