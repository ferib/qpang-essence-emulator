#ifndef GC_SHOOP_EVENT_HPP
#define GC_SHOOP_EVENT_HPP

#include "game_net_event.hpp"

#include "cg_shoot.hpp"

class GCShoot : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	GCShoot() : GameNetEvent{ GC_SHOOT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCShoot(CGShoot shoot) : GameNetEvent{ GC_SHOOT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->playerId = shoot.playerId;
		this->itemId = shoot.itemId;
		this->unk_03 = shoot.unk_02;
		this->unk_04 = shoot.unk_04;
		this->unk_05 = shoot.unk_05;
		this->unk_06 = shoot.unk_06;
		this->unk_07 = shoot.unk_07;
		this->unk_08 = shoot.unk_08;
		this->unk_09 = shoot.unk_09;
		this->unk_10 = shoot.unk_03;
		this->isP2P = false;
	};
	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(playerId);
		bstream->write(itemId);
		bstream->write(unk_03);
		bstream->write(unk_04);
		bstream->write(unk_05);
		bstream->write(unk_06);
		bstream->write(unk_07);
		bstream->write(unk_08);
		bstream->write(unk_09);
		bstream->write(unk_10);
		bstream->write(isP2P);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 playerId;
	U32 itemId;
	F32 unk_03;
	F32 unk_04;
	F32 unk_05;
	F32 unk_06;
	F32 unk_07;
	F32 unk_08;
	F32 unk_09;
	F32 unk_10;
	U32 isP2P;

	TNL_DECLARE_CLASS(GCShoot);
};


#endif // !GC_ARRANGED_ACCEPT_HPP