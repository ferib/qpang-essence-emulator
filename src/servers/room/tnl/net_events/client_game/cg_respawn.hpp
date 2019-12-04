#ifndef CG_RESPAWN_H
#define CG_RESPAWN_H

#include "game_net_event.hpp"
class CGRespawn : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	enum CMD : U32 
	{
		OUR = 2,
		OTHER = 4,
	};

	CGRespawn() : GameNetEvent{ CG_RESPAWN, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->read(&unk_01);
		bstream->read(&unk_02);
		bstream->read(&unk_03);
	};
	void process(EventConnection* ps) 
	{
		NET_POST_EVENT(ps);
	};

	U32 unk_01;
	U8 unk_02;
	U32 unk_03;

	TNL_DECLARE_CLASS(CGRespawn);
};
#endif