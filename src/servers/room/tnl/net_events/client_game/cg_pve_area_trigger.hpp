#ifndef CG_PVE_AREA_TRIGGER_H
#define CG_PVE_AREA_TRIGGER_H

#include "game_net_event.hpp"
class CGPvEAreaTrigger : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGPvEAreaTrigger() : GameNetEvent{ CG_PVE_AREA_TRIGGER, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};

	U32 flag;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->read(&flag);
	};
	void process(EventConnection* ps) 
	{
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGPvEAreaTrigger);
};
#endif