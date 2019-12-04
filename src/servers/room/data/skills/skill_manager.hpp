#ifndef SKILL_MANAGER_HPP
#define SKILL_MANAGER_HPP

#include "database.hpp"
#include "skill.hpp"

#include <map>
#include <cstdint>
#include <string>

class SkillManager
{
public:
	SkillManager();
	~SkillManager();

	void Load();

	Skill GetSkill(uint32_t itemId);
	std::string GetName(uint32_t itemId);
	uint32_t GetPointCost(uint32_t itemId);
	uint32_t GetDuration(uint32_t skillId);

	uint32_t GetRandomSkillId();

private:
	std::map<uint32_t, Skill> _skills;
};


#endif // !SKILL_MANAGER_HPP