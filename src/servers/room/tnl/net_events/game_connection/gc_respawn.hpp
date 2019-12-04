#ifndef GC_RESPAWN_HPP
#define GC_RESPAWN_HPP

#include "game_net_event.hpp"

class GCRespawn : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	GCRespawn() : GameNetEvent{ GC_RESPAWN, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCRespawn(U32 playerId, U32 characterId, U32 cmd, F32 x, F32 y, F32 z) : GameNetEvent{ GC_RESPAWN, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny }
	{
		this->playerId = playerId;
		this->cmd = cmd;
		this->characterIdentifier = characterId,
		this->x = x;
		this->y = y;
		this->z = z;
		this->unk_02 = 2;
	};
	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(cmd);
		bstream->write(playerId);
		bstream->write(characterIdentifier);
		bstream->write(x);
		bstream->write(y);
		bstream->write(z);
		bstream->write(unk_02);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 playerId;
	U32 cmd;
	U32 characterIdentifier;
	F32 x;
	F32 y;
	F32 z;
	U8 unk_02;

	TNL_DECLARE_CLASS(GCRespawn);
};

#endif // !GC_ARRANGED_ACCEPT_HPP