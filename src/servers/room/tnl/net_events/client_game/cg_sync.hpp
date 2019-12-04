#ifndef CG_SYNC_H
#define CG_SYNC_H

#include "game_net_event.hpp"

class CGSync : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGSync() : GameNetEvent{ CG_SYNC, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	U32 cmd;
	U32 playerId;
	U32 unk_03;
	F32 xPos;
	F32 yPos;
	F32 zPos;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&cmd);
		bstream->read(&playerId);
		bstream->read(&unk_03);
		bstream->read(&xPos);
		bstream->read(&yPos);
		bstream->read(&zPos);
	};
	void process(EventConnection* ps)
	{
		auto player = sGame->FindPlayer(ps, playerId);
		if (player != nullptr)
		{
			//auto room = player->GetRoom();
			//if (room)
			//{
			//	room->OnPlayerSync(*this);
			//}
		}
		
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGSync);
};
#endif