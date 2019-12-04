#ifndef CG_GAME_ITEM_H
#define CG_GAME_ITEM_H

#include "game_net_event.hpp"

class CGGameItem : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	enum CMD : U8
	{
		PICKUP = 1,
		SPAWN = 6,
		REFILL_AMMO = 14
	};

	CGGameItem() : GameNetEvent{ CG_GAME_ITEM, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&unk_02); // cmd?
		bstream->read(&unk_03);
		bstream->read(&unk_04);
		bstream->read(&unk_05);
		bstream->read(&unk_06);
		bstream->read(&uid); // uid
	};
	void process(EventConnection* ps)
	{
		auto player = sGame->FindPlayer(ps, playerId);
		if (player != nullptr)
		{
			//auto room = player->GetRoom();
			//if (room)
			//	room->OnPlayerPickupItem(*this);
		}

		NET_POST_EVENT(ps);
	};

	U32 playerId;
	U32 unk_02;
	U32 unk_03;
	U32 unk_04;
	U32 unk_05;
	U32 unk_06;
	U32 uid; // uid of the game item the player picks up

	TNL_DECLARE_CLASS(CGGameItem);
};
#endif