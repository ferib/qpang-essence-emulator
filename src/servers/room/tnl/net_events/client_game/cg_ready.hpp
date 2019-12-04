#ifndef CG_READY_H
#define CG_READY_H

#include "game_net_event.hpp"
#include "gc_ready.hpp"

class CGReady : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	enum CMD : U32
	{
		UNREADY = 0,
		READY = 1,
	};

	CGReady() : GameNetEvent{ CG_READY, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&cmd);
	};

	void handle(Player::Ptr player)
	{
	}

	void process(EventConnection* ps)
	{
		auto player = sGame->FindPlayer(ps);

		if (player != nullptr)
		{
			if (player->GetState() != PlayerState::IDLING && player->GetState() != PlayerState::READY)
			{
				player->Send(new GCReady(player->GetIdentifier(), CMD::UNREADY));

				return sGame->Whisper(player, "Seems like you can't do this action quite yet");
			}

			auto room = player->GetRoom();
			if (room != nullptr)
			{
				if (room->IsPlaying())
				{
					if (room->GetState() == RoomState::ENDING)
					{
						return sGame->Whisper(player, "This game is ending... please wait!");
					}

					const auto session = room->GetSession();
					session->AddPlayer(player);
					player->GetConnection()->EnterGame(player);
				}
				else
				{
					const auto state = cmd == CMD::READY ? PlayerState::READY : PlayerState::IDLING;

					player->SetState(state);
					room->Broadcast<GCReady>(player->GetIdentifier(), state);
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	U32 playerId;
	U32 cmd;

	TNL_DECLARE_CLASS(CGReady);
};
#endif