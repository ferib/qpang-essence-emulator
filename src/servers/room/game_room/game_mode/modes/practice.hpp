#ifndef _PRACTICE_HPP
#define _PRACTICE_HPP

//std
#include <string>
#include <memory>
#include "game_mode.hpp"

class GameRoom;

class Practice : public GameMode
{

public:
	Practice() = default;
	~Practice() = default;

	void OnApply(const std::shared_ptr<GameRoom>& room) override;	
	bool IsTeamMode() override;

	std::string GetName() override;
	uint8_t GetModeIdentifier() override;
};

#endif //_PRACTICE_HPP