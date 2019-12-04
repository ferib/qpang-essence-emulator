#ifndef CG_GAME_STATE_H
#define CG_GAME_STATE_H

#include "game_net_event.hpp"

#include "gc_room_info.hpp"
#include "game.hpp"
#include "game_connection.hpp"
#include "gc_game_state.hpp"
#include "request_player_equipment_event.hpp"

class CGGameState : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	enum State : U32 {
		GAME_WAITING_PLAYERS_SPECTATE_UNK = 1,
		GAME_FORCE_LEAVE_STO = 2,
		GAME_WAITING_PLAYERS = 3,
		SEND_GAME_STATE_PLAY = 4,
		GAME_FORCE_DISCONNECT = 7,
		REMOVE_INVINCIBILITY = 8,
		SYNC_TIME = 11,
		GAME_START = 12,
		GAME_START_PVE = GAME_START,
		GAME_STATE_P2P_FAIL = 14,
		LEAVE_GAME = 15,
		UPDATE_HEALTH = 16,
		KILLFEED_ADD = 17,
		PLAYER_STATE_HACK = 22,
		GAME_OVER = 23,
		INV_IN = 24,
		INV_OUT = 25,
		KILLFEED_ADD_HEAD = 28,
		START_RESPAWN_TIMER = 29,
	};
	CGGameState() : GameNetEvent{ CG_GAME_STATE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&cmd);
		bstream->read(&data);
		bstream->read(&unk_04);
		bstream->read(&unk_05);
		bstream->read(&unk_06);
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
				switch (cmd)
				{
				case State::LEAVE_GAME:
					room->OnPlayerLeft(player);
					room->Broadcast<GCGameState>(player->GetIdentifier(), State::LEAVE_GAME);

					player->GetConnection()->SetRoomInfo(room);

					room->RemovePlayerFromRoom(player);
					room->AddPlayerToRoom(player);
					player->GetConnection()->AddPlayerToRoom(player);

					break;

				case State::INV_IN:
					player->SetState(INVENTORY);
					room->Broadcast<GCGameState>(player->GetIdentifier(), State::INV_IN);
					break;
				case State::INV_OUT:
					room->Broadcast<GCGameState>(player->GetIdentifier(), State::INV_OUT);
					sGame->Lobby()->SendPacket(RequestPlayerEquipmentEvent{ player }.Compose(nullptr));
					break;
				case State::GAME_WAITING_PLAYERS:
					room->OnPlayerLoaded(player);
					break;
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	U32 playerId;
	U32 cmd;
	U32 data;
	U32 unk_04;
	U32 unk_05;
	U32 unk_06;

	TNL_DECLARE_CLASS(CGGameState);
};
#endif