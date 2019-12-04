#ifndef GC_EXIT_HPP
#define GC_EXIT_HPP

#include "game_net_event.hpp"

class GCExit : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	GCExit() : GameNetEvent{ GC_EXIT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCExit(U32 playerId, U32 cmd, U32 masterId) : GameNetEvent{ GC_EXIT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } 
	{
		this->playerId = playerId;
		this->cmd = cmd;
		this->masterId = masterId;
	};
	void pack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->write(playerId);
		bstream->write(cmd);
		bstream->write(masterId);
		bstream->write(unk_01);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 playerId;
	U32 cmd;
	U32 masterId;
	U32 unk_01 = 0;

	TNL_DECLARE_CLASS(GCExit);
};

#endif // !GC_ARRANGED_ACCEPT_HPP