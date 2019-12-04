#ifndef ROOM_STATE_HPP
#define ROOM_STATE_HPP

#include <cstdint>

enum RoomState : uint8_t {
	CLOSED = 0x01,
	WAITING = 0x02,
	PLAYING = 0x08,
	PLAYING_UNK = 0x09,
	ENDING = 0x10,
};

#endif