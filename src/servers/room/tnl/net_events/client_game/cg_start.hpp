#ifndef CG_START_H
#define CG_START_H

#include "game_net_event.hpp"
#include "gc_start.hpp"

class CGStart : public GameNetEvent
{
	typedef NetEvent Parent;

public:
	U32 playerId; //88
	U8 unk_01; //92

	CGStart() : GameNetEvent{ CG_START, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&unk_01);
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
				if (room->IsPlaying())
				{
					auto session = room->GetSession();

					session->AddPlayer(player);
					return player->GetConnection()->EnterGame(player);
				}

				if (player->GetIdentifier() != room->GetMasterIdentifier())
					return;

				player->SetState(PlayerState::READY);

				room->Start();
			}

		}
		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGStart);
};
#endif