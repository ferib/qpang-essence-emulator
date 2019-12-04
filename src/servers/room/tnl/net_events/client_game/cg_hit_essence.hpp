#ifndef CG_HIT_ESSENCE_H
#define CG_HIT_ESSENCE_H

#include "game_net_event.hpp"
class CGHitEssence : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGHitEssence() : GameNetEvent{ CG_HIT_ESSENCE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	U32 unk_01;
	U32 unk_02;
	U32 unk_03;
	U32 unk_04;
	U32 unk_05;
	U32 unk_06;
	U8 unk_07;
	U32 unk_08;
	U8 unk_09;
	U32 unk_10;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->read(&unk_01);
		bstream->read(&unk_02);
		bstream->read(&unk_03);
		bstream->read(&unk_04);
		bstream->read(&unk_05);
		bstream->read(&unk_06);
		bstream->read(&unk_07);
		bstream->read(&unk_08);
		bstream->read(&unk_09);
		bstream->read(&unk_10);
	};
	void process(EventConnection* ps) 
	{
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGHitEssence);
};

#endif