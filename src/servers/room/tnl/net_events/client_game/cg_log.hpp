#ifndef CG_LOG_H
#define CG_LOG_H

#include "game_net_event.hpp"
class CGLog : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGLog() : GameNetEvent{ CG_LOG, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	char buf[256];

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->readString(buf);
	};
	void process(EventConnection* ps)
	{
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGLog);
};
#endif