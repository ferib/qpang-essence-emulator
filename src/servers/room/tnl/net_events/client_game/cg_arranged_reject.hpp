#ifndef CG_ARRANGED_REJECT_HPP
#define CG_ARRANGED_REJECT_HPP

#include "game_net_event.hpp"
class CGArrangedReject : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGArrangedReject() : GameNetEvent{ CG_ARRANGED_REJECT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	U32 unk_01;
	U32 unk_02;
	U32 unk_03;
	ByteBuffer* unk_04;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		unk_04 = new ByteBuffer();
		bstream->read(&unk_01);
		bstream->read(&unk_02);
		bstream->read(&unk_03);
		bstream->read(unk_04);
	};
	void process(EventConnection* ps) 
	{
		unk_04->clear();
		unk_04->destroySelf();
	};

	TNL_DECLARE_CLASS(CGArrangedReject);
};
#endif