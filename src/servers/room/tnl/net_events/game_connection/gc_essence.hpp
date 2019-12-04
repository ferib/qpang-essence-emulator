#ifndef GC_ESSENCE_HPP
#define GC_ESSENCE_HPP

#include "game_net_event.hpp"

class GCEssence : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCEssence() : GameNetEvent{ CG_ESSENCE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};

	U32 unk_01;
	U32 unk_02;
	U32 unk_03;
	U32 unk_04;
	U32 unk_05;
	U32 unk_06;
	U32 unk_07;
	U32 unk_08;
	U32 unk_09;
	U32 unk_10;

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(unk_01);
		bstream->write(unk_02);
		bstream->write(unk_03);
		bstream->write(unk_04);
		bstream->write(unk_05);
		bstream->write(unk_06);
		bstream->write(unk_07);
		bstream->write(unk_08);
		bstream->write(unk_09);
		bstream->write(unk_10);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	TNL_DECLARE_CLASS(GCEssence);
};

#endif // !GC_ARRANGED_ACCEPT_HPP