#ifndef CG_EXIT_H
#define CG_EXIT_H

#include "game_net_event.hpp"

#include "cg_game_state.hpp"
#include "gc_join.hpp"

#include "game_room.hpp"
#include "game_connection.hpp"
#include "gc_disconnect.hpp"

class CGExit : public GameNetEvent
{
	typedef NetEvent Parent;


public:

	enum Command : U8
	{
		LEAVE = 0,
		KICK = 1,
		MASTER_KICK_IDLE = 2,
	};

	CGExit() : GameNetEvent{ CG_EXIT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};
	CGExit(U32 playerId, U8 cmd)
	{
		this->playerId = playerId;
		this->cmd = cmd;
	}

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(playerId);
		bstream->write(cmd);
	};

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
			auto room = player->GetRoom();
			if (room != nullptr)
			{
				if (cmd == LEAVE)
				{
					sGame->RemovePlayerFromRoom(room, player);
				}

				if (cmd == KICK)
				{
					if (player->GetIdentifier() == room->GetMasterIdentifier())
					{
						auto playerToKick = sGame->FindPlayer(playerId);

						if (playerToKick != nullptr)
						{
							sGame->RemovePlayerFromRoom(room, playerToKick);
							playerToKick->GetConnection()->disconnect("You got kicked, bye.");
						}
					}
				}

				if (cmd == MASTER_KICK_IDLE)
				{
					if (player->GetIdentifier() == room->GetMasterIdentifier())
					{
						sGame->RemovePlayerFromRoom(room, player);

						player->GetConnection()->disconnect("Congratulations, you just idle kicked yourself");
					}
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	U32 playerId;
	U8 cmd;

	TNL_DECLARE_CLASS(CGExit);
};
#endif