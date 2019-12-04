#ifndef GC_TARGET_HPP
#define GC_TARGET_HPP

#include "game_net_event.hpp"
#include "cg_target.hpp"

class GCTarget : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCTarget() : GameNetEvent{ GC_TARGET, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient } {};
	GCTarget(CGTarget& target) : GameNetEvent{ GC_TARGET, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		cmd = target.cmd;
		playerId = target.playerId;
		targetId = target.targetId;
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(cmd);
		bstream->write(playerId);
		bstream->write(targetId);
		bstream->write(U32(0)); // LOBYTE(result) = BitStream::Read(v3, 32u, &a3);
		// 1 will crash the game ^
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 cmd;
	U32 playerId;
	U32 targetId;

	TNL_DECLARE_CLASS(GCTarget);
};

#endif // !GC_ARRANGED_ACCEPT_HPP