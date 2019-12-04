#ifndef CG_ROOM_HPP
#define CG_ROOM_HPP

#include "game_net_event.hpp"
#include "game.hpp"
#include "game_mode.hpp"

#include "game_connection.hpp"
#include "gc_room.hpp"

class CGRoom : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	CGRoom() : GameNetEvent{ CG_ROOM, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&cmd);
		bstream->read(&value);
		bstream->read(&mode);
		bstream->read(&memberCount);
		bstream->read(&goal);
		char buf[256];
		bstream->readString(buf);
		password = buf;
		title = ReadBuffer(bstream);
		bstream->read(&timeAmount);
		bstream->read(&isRounds);
		bstream->read(&unk_11);
		bstream->read(&unk_12);
		bstream->read(&unk_13);
		bstream->read(&unk_14);
		bstream->read(&_160);
		bstream->read(&_161);
		bstream->read(&_162);
		bstream->read(&_163);
		bstream->read(&unk_19);
		bstream->read(&unk_20);
		bstream->read(&unk_21);
		bstream->read(&unk_22);
	};

	void handle(Player::Ptr player)
	{

	}

	void process(EventConnection* ps)
	{

		auto player = sGame->FindPlayer(ps);

		if (player != nullptr)
		{
			if (cmd == Command::CREATE_ROOM)
			{
				if (player->GetRoom() != nullptr)
					return;

				//PvE Disabled
				if (mode == 9)
					return;

				auto room = sGame->CreateRoom(title, value, mode);
				room->AddPlayer(player);

				room->SetNewMaster(playerId);

				player->GetConnection()->CreateRoom(playerId, 9, room);
				player->GetConnection()->SetRoomInfo(room);
				player->GetConnection()->AddPlayerToRoom(player);

				player->SetState(PlayerState::IDLING);
			}
			else if (cmd == Command::JOIN_ROOM)
			{
				if (player->GetRoom() == nullptr)
				{
					auto room = sGame->GetRoom(roomId);

					if (room != nullptr)
					{
						if (room->GetMaxPlayerCount() <= room->GetPlayerCount())
							return;

						room->AddPlayer(player);

						player->GetConnection()->CreateRoom(playerId, 9, room);
						player->GetConnection()->SetRoomInfo(room);

						room->AddPlayerToRoom(player);

						player->SetState(PlayerState::IDLING);
					}
				}
			}

			else
			{
				auto room = player->GetRoom();
				if (room != nullptr)
				{

					if (room->GetMasterIdentifier() == player->GetIdentifier())
					{
						switch (cmd)
						{
						case PLAYERS_ROOM:
							room->SetMaxPlayerCount(value);
							break;
						case MAP_ROOM:
							room->SetMap(value);
							break;
						case MODE_ROOM:
							room->SetMode(sGame->FindGameMode(mode));
							break;
						case PASS_ROOM:
							room->SetPassword(password);
							break;
						case SET_POINTS:
							room->SetPointsGoal(value);
							room->SetPointsGame(true);
							break;
						case SET_TIME:
							room->SetTimeGoal(value);
							room->SetPointsGame(false);
							break;
						case TOGGLE_SKILL:
							sGame->Whisper(player, "Skills are disabled in this server");
							return;
						case TOGGLE_MELEE:
							sGame->Whisper(player, "Melee-only games are disabled (for now)");
							return;
						default:
							sGame->Whisper(player, "This functionality is not implemented yet, please contact an administrator");
							return;
							break;
						}

						room->Broadcast<GCRoom>(player->GetIdentifier(), cmd, value, mode);
					}
				}
			}
		}

		NET_POST_EVENT(ps);
	}


	enum Command : uint32_t
	{
		MAP_ROOM = 1,
		PLAYERS_ROOM = 2,
		MODE_ROOM = 3,
		SET_POINTS = 4,
		PASS_ROOM = 5,
		CREATE_ROOM = 6,
		JOIN_ROOM = 7,
		SET_TIME = 20,
		LEVEL_ROOM = 23,
		TEAM_ROOM = 25,
		TOGGLE_SKILL = 26,
		CREATE_EVENT_ROOM = 27,
		TOGGLE_MELEE = 30,
	};



	U32 playerId; //92
	U32 cmd; //96
	U32 value; //100

	union {
		U8 mode; //109
		U8 roomId;
	};

	union {
		U8 memberCount; //110
		U8 roomId2;
	};

	U8 goal; //111
	std::string password; //104
	std::wstring title; //112

	union
	{
		U8 timeAmount;
		U8 pointsAmount;
	};

	U8 isRounds; //155
	U32 unk_11; //156

	U32 unk_12; //164

	U16 unk_13; //168
	U32 unk_14; //188

	U8 _160; //160
	U8 _161; //161
	U8 _162; //162
	U8 _163; //163

	U32 unk_19; //184
	U32 unk_20; //180
	U32 unk_21; //172
	U32 unk_22; //176

	TNL_DECLARE_CLASS(CGRoom);
};
#endif