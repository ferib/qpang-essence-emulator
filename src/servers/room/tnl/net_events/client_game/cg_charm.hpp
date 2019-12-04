#ifndef CG_CHARM_HPP
#define CG_CHARM_HPP

#include "game_net_event.hpp"

class CGCharm : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGCharm() : GameNetEvent{ CG_CHARM, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	U32 unk_01;
	U32 unk_02;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->read(&unk_01);
		bstream->read(&unk_02);
	};
	void process(EventConnection* ps) 
	{
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGCharm);
};

#endif