#ifndef CG_PVE_RESPAWN_REQ_H
#define CG_PVE_RESPAWN_REQ_H

#include "game_net_event.hpp"
class CGPvERespawnReq : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGPvERespawnReq() : GameNetEvent{ CG_PVE_RESPAWN_REQ, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};

	U32 playerId;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->read(&playerId);
	};
	void process(EventConnection* ps) 
	{
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGPvERespawnReq);
};
#endif