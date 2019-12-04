#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <cstdint>

enum PlayerState : uint8_t {
	IDLING = 0,
	READY = 1,
	INVENTORY = 2,
	LOADING = 3,
	WAITING_FOR_PLAYERS = 4,
	IN_GAME = 5,
	RESULT_SCREEN = 6,
	IN_SQUARE = 7,
};

#endif