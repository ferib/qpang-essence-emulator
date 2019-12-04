#ifndef GC_ROOM_INFO_HPP
#define GC_ROOM_INFO_HPP

#include "game_net_event.hpp"
#include "game_room.hpp"
#include "game_mode.hpp"

class GCRoomInfo : public GameNetEvent
{
	typedef NetEvent Parent;

public:
	GCRoomInfo() : GameNetEvent{ GC_ROOM_INFO, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCRoomInfo(GameRoom::Ptr room) : GameNetEvent{ GC_ROOM_INFO, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->masterUid = room->GetMasterIdentifier();
		this->joinNum = room->GetMaxPlayerCount();
		this->gameMode = room->GetMode()->GetModeIdentifier();
		this->goalPoint = room->IsPointsGame() ? room->GetPointGoal() : room->GetTimeGoal();
		this->mapNum = room->GetMap();
		this->roomState = room->IsPlaying() ? RoomState::PLAYING : RoomState::WAITING;
		this->respawnTime = 10 * 1000;
		this->p2pWaitTime = 6000;
		this->title = room->GetName();
		this->isTime = !room->IsPointsGame();
		this->rounds = 2;
		this->levelLimit = false;
		this->gameId = room->GetIdentifier();
		this->teamBalance = false;
		this->skillMode = false;
		this->pingLevel = NULL;
		this->melee = false;
		this->event = false;
		
	}
	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(masterUid); //88
		bstream->write(joinNum); //134 
		bstream->write(gameMode); //136 
		bstream->write(goalPoint); //140
		bstream->write(mapNum); //144
		bstream->write(roomState); //148
		bstream->write(respawnTime); //152
		bstream->write(p2pWaitTime); //154 
		WriteBuffer(bstream, title);
		bstream->write(isTime); //156
		bstream->write(rounds); //157
		bstream->write(levelLimit); //164
		bstream->write(gameId); //160
		bstream->write(teamBalance); //165
		bstream->write(skillMode); //166
		bstream->write(pingLevel); //167
		bstream->write(melee); //168
		bstream->write(event); //169
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 masterUid; //88
	U16 joinNum; //134 
	U16 gameMode; //136 
	U32 goalPoint; //140

	U16 mapNum; //144
	U32 roomState; //148
	U16 respawnTime; //152
	U16 p2pWaitTime; //154 

	std::string title; //172

	U8 isTime; //156
	U8 rounds; //157
	U8 levelLimit; //164
	U32 gameId; //160
	U8 teamBalance; //165
	U8 skillMode; //166
	U8 pingLevel; //167
	U8 melee; //168
	U8 event; //169

	TNL_DECLARE_CLASS(GCRoomInfo);
};

#endif // !GC_ARRANGED_ACCEPT_HPP