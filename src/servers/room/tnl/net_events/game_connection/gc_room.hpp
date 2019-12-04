#ifndef GC_ROOM_HPP
#define GC_ROOM_HPP

#include <string>
#include <cstdint>
#include "game_net_event.hpp"
#include "game_room.hpp"
#include "game_mode.hpp"


class GCRoom : public GameNetEvent
{
	typedef NetEvent Parent;

public:
	GCRoom() : GameNetEvent{ GC_ROOM, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};

	GCRoom(uint32_t playerId, uint32_t cmd, GameRoom::Ptr room)
	{
		this->zero = 0;
		this->playerId = playerId;
		this->cmd = cmd;
		this->roomId = room->GetIdentifier();
		this->mode = room->GetMode()->GetModeIdentifier();
		this->memberCount = room->GetPlayerCount();
		this->title = room->GetName();
	};

	GCRoom(const uint32_t& playerIdentifier, const uint32_t& cmd, const uint32_t& value, const uint32_t& mode)
	{
		this->zero = 0;
		this->playerId = playerIdentifier;
		this->cmd = cmd;
		this->value = value;
		this->mode = mode;
		this->title = "-";
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(playerId);
		bstream->write(cmd);
		bstream->write(value);

		bstream->write(mode);
		bstream->write(memberCount);
		bstream->write(goal);

		bstream->writeString(password.c_str(), 255);
		WriteBuffer(bstream, title);
		bstream->write(time);
		bstream->write(rounds);
		bstream->write(_160);

		bstream->write(zero);

		bstream->write(_161);
		bstream->write(_162);
		bstream->write(_163);
	};

	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 playerId; //92
	U32 cmd; //96

	union
	{
		U32 value; //100
		U32 roomId; //100
	};


	U8 mode; //109
	U8 memberCount; //110
	U8 goal = 5; //111

	std::string password;
	std::string title;
	U8 time = 6; //154

	union
	{
		U8 rounds = 1; //155 
		U8 gameId; //might be u8
	};

	U8 _160 = 1; //156 //In CGRoom

	U32 zero = 0; //set to 0
	U8 _161 = 1; //164
	U8 _162 = 1; //165
	U8 _163 = 1; //166



	TNL_DECLARE_CLASS(GCRoom);
};

#endif // !GC_ARRANGED_ACCEPT_HPP