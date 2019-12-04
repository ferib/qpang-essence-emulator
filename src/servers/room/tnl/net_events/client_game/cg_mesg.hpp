#ifndef CG_MESG_H
#define CG_MESG_H

#include "game_net_event.hpp"
#include "gc_mesg.hpp"

class CGMesg : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	CGMesg() : GameNetEvent{ CG_MESG, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&cmd);
		nickname = ReadBuffer(bstream);
		message = ReadBuffer(bstream);
	};

	void handle(Player::Ptr player)
	{
	}

	void process(EventConnection* ps)
	{

		auto player = sGame->FindPlayer(ps);

		if (player != nullptr)
		{
			auto room = player->GetRoom();

			if (room != nullptr)
			{
				room->Broadcast<GCMesg>(player->GetIdentifier(), cmd, nickname, message);
			}
		}

		NET_POST_EVENT(ps);
	};


	U32 playerId;
	U32 cmd;
	std::wstring nickname;
	std::wstring message;

	TNL_DECLARE_CLASS(CGMesg);
};
#endif