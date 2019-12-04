#ifndef GC_MOVE_HPP
#define GC_MOVE_HPP

#include "game_net_event.hpp"
#include "cg_move.hpp"

class GCMove : public GameNetEvent
{

	typedef NetEvent Parent;
public:
	GCMove() : GameNetEvent{ GC_MOVE, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirServerToClient } {};
	GCMove(CGMove move) : GameNetEvent{ GC_MOVE, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirServerToClient }
	{
		this->playerId = move.playerId;
		this->cmd = move.cmd;
		this->unk_01 = move.unk_01;
		this->unk_02 = move.unk_02;
		this->unk_03 = move.unk_03;
		this->unk_04 = move.unk_04;
		this->unk_05 = move.unk_05;
		this->unk_06 = move.unk_06;
		this->unk_07 = move.unk_07;
		this->unk_08 = move.unk_08;
		this->unk_09 = move.unk_09;
		this->unk_10 = move.unk_10;
	};

	U32 playerId;
	U32 cmd;
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
	U8 unk_11 = 0;

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(playerId);
		bstream->write(cmd);
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
		bstream->write(unk_11);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	TNL_DECLARE_CLASS(GCMove);
};

#endif // !GC_ARRANGED_ACCEPT_HPP