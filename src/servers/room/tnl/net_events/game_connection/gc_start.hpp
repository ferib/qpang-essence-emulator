#ifndef GC_START_HPP
#define GC_START_HPP

#include "game_net_event.hpp"

class GCStart : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	U32 playerId;

	U32 unk_01;
	U32 unk_02;

	U16 map;
	U16 mode;

	GCStart() : GameNetEvent{ GC_START, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCStart(const Player::Ptr& player) : GameNetEvent{ GC_START, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny }
	{
		this->playerId = player->GetIdentifier();

		auto room = player->GetRoom();

		this->map = room->GetMap();
		this->mode = room->GetMode()->GetModeIdentifier();
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{	
		bstream->write(playerId);
		bstream->write(2);
		bstream->write(unk_02);
		bstream->write(map);
		bstream->write(mode);
	};

	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	TNL_DECLARE_CLASS(GCStart);
};

#endif // !GC_ARRANGED_ACCEPT_HPP