#ifndef CG_PVE_ROUND_START_H
#define CG_PVE_ROUND_START_H

#include "game_net_event.hpp"
class CGPvERoundStart : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGPvERoundStart() : GameNetEvent{ CG_PVE_ROUND_START, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) 
	{
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGPvERoundStart);
};
#endif