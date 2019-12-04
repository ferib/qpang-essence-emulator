#ifndef CC_CHARM_H
#define CC_CHARM_H

#include "game_net_event.hpp"

class CCCharm : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CCCharm() : GameNetEvent{ CC_CHARM, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};

	U32 unk_01;
	U32 unk_02;
	U32 unk_03;
	U32 unk_04;
	U8 unk_05;

	void pack(EventConnection* conn, BitStream* bstream)
	{

	};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&unk_01);
		bstream->read(&unk_02);
		bstream->read(&unk_03);
		bstream->read(&unk_04);
		bstream->read(&unk_05);
	};

	void process(EventConnection* ps)
	{
	};

	TNL_DECLARE_CLASS(CCCharm);
};
#endif