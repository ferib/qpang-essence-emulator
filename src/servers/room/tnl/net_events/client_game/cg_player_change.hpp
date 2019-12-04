#ifndef CG_PLAYER_CHANGE_H
#define CG_PLAYER_CHANGE_H

#include "game_net_event.hpp"
#include "gc_player_change.hpp"

class CGPlayerChange : public GameNetEvent
{
	typedef NetEvent Parent;


public:

	enum CMD {
		CHARACTER = 1,
		TEAM = 2,
	};

	CGPlayerChange() : GameNetEvent{ CG_PLAYER_CHANGE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&cmd);
		bstream->read(&value);
	};

	void process(EventConnection* ps)
	{
		auto player = sGame->FindPlayer(ps, playerId);

		if (player != nullptr)
		{
			auto room = player->GetRoom();

			if (room != nullptr)
			{
				if (cmd == CHARACTER)
				{
					switch (value)
					{
					case 579:
						player->SetCharacter(MIUMIU);
						break;
					case 578:
						player->SetCharacter(KUMA);
						break;
					case 333:
						player->SetCharacter(KEN);
						break;
					case 343:
						player->SetCharacter(HANA);
						break;
					case 850:
						player->SetCharacter(SAI);
						break;
					case 851:
						player->SetCharacter(URU);
						break;
					default:
						value = KEN;
						player->SetCharacter(KEN);
					}

					room->Broadcast<GCPlayerChange>(player, CHARACTER, player->GetCharacter());
				}

				else if (cmd == TEAM)
				{
					switch (value)
					{
					case 1:
						player->SetTeam(BLUE);
						break;
					case 2:
						player->SetTeam(YELLOW);
						break;
					default:
						value = BLUE;
						player->SetTeam(BLUE);
					}

					room->Broadcast<GCPlayerChange>(player, TEAM, value);
				}

			}
		}

		NET_POST_EVENT(ps);
	};

	U32 playerId;
	U8 cmd;
	U32 value;

	TNL_DECLARE_CLASS(CGPlayerChange);
};
#endif