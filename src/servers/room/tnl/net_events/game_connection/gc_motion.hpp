#ifndef GC_MOTION_HPP
#define GC_MOTION_HPP

#include "game_net_event.hpp"
#include "cg_motion.hpp"

class GCMotion : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCMotion() : GameNetEvent{ GC_MOTION, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirAny } {};
	GCMotion(CGMotion motion) : GameNetEvent{ GC_MOTION, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirServerToClient }
	{
		this->cmd = motion.cmd;
		this->unk_02 = motion.unk_02;
		this->unk_03 = motion.unk_03;
		this->unk_04 = motion.unk_04;
		this->unk_05 = motion.unk_05;
		this->unk_06 = motion.unk_06;
		this->unk_07 = motion.unk_07;
		this->unk_08 = motion.unk_08;
		this->unk_09 = motion.unk_09;
		this->playerId = motion.playerId;
		this->isP2P = false;
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{
		 bstream->write(cmd);
		 bstream->write(unk_02);
		 bstream->write(unk_03);
		 bstream->write(unk_04);
		 bstream->write(unk_05);
		 bstream->write(unk_06);
		 bstream->write(unk_07);
		 bstream->write(unk_08);
		 bstream->write(unk_09);
		 bstream->write(playerId);
		 bstream->write(isP2P);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 cmd;
	U32 unk_02;
	U32 unk_03;
	U32 unk_04;
	U32 unk_05;
	U32 unk_06;
	U32 unk_07;
	U32 unk_08;
	U32 unk_09;
	U32 playerId;
	U32 isP2P;

	TNL_DECLARE_CLASS(GCMotion);
};

#endif // !GC_ARRANGED_ACCEPT_HPP