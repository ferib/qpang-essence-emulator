#ifndef CG_SCORE_H
#define CG_SCORE_H

#include "game_net_event.hpp"
#include "gc_score.hpp"

class CGScore : public GameNetEvent
{
	typedef NetEvent Parent;


public:
	CGScore() : GameNetEvent{ CG_SCORE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};
	U32 cmd;

	enum CMD {
		GAME = 200,
		USER = 100
	};

	void pack(EventConnection* conn, BitStream* bstream) {};

	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&cmd);
	};

	void handle(Player::Ptr player)
	{
	}

	void process(EventConnection* ps)
	{
		if (cmd == USER)
		{
			auto player = sGame->FindPlayer(ps);
			if (player != nullptr)
			{
				auto room = player->GetRoom();
				if (room != nullptr)
				{
					auto session = room->GetSession();
					if (session != nullptr)
					{
						player->Send(new GCScore(session, false));
					}
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGScore);
};
#endif