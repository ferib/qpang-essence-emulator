#ifndef GC_SYNC_HPP
#define GC_SYNC_HPP

#include "game_net_event.hpp"
#include "cg_sync.hpp"

class GCSync : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCSync() : GameNetEvent{ GC_SYNC, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCSync(CGSync& sync) : GameNetEvent{ GC_SYNC, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->cmd = sync.cmd;
		this->playerId = sync.playerId;
		this->unk_03 = sync.unk_03;
		this->xPos = sync.xPos;
		this->yPos = sync.yPos;
		this->zPos = sync.zPos;
		this->isP2P = false;
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(cmd);
		bstream->write(playerId);
		bstream->write(unk_03);
		bstream->write(xPos);
		bstream->write(yPos);
		bstream->write(zPos);
		bstream->write(isP2P);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 cmd;
	U32 playerId;
	U32 unk_03;
	F32 xPos;
	F32 yPos;
	F32 zPos;
	U8 isP2P;

	TNL_DECLARE_CLASS(GCSync);
};

#endif // !GC_ARRANGED_ACCEPT_HPP