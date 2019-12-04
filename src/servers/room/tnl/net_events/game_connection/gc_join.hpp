#ifndef GC_JOIN_HPP
#define GC_JOIN_HPP

#include "game_net_event.hpp"
#include "player.hpp"

class GCJoin : public GameNetEvent
{
	typedef NetEvent Parent;

public:
	GCJoin() : GameNetEvent{ GC_JOIN, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient } {};
	GCJoin(Player::Ptr player) : GameNetEvent{ GC_JOIN, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->nickname = player->GetName();

		this->state = 0x20;
		this->playerId = player->GetIdentifier();
		this->characterId = player->GetCharacter();
		this->selectedWeapon = player->GetSession() != nullptr ? player->GetSession()->GetWeapon() : player->GetEquipment()->GetDefaultWeapon();
		this->team = player->GetTeam();
		this->ready = player->IsReady();
		this->weaponCount = player->GetEquipment()->GetWeapons().size();
		this->weaponIds = player->GetEquipment()->GetWeapons();
		this->armor = player->GetEquipment()->GetArmor();
		this->playerRank = player->GetRank();
		this->life = player->GetSession() != nullptr ? player->GetSession()->GetDefaultHealth() : 100;
		this->refers = player->GetPrestige();
		this->level = player->GetLevel();
		this->experience = player->GetExperience();
	}

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(state); //88 //either 20h, 40h, 80h
		bstream->write(playerId); //92
		bstream->write(characterId); //130
		bstream->write(selectedWeapon); //168
		bstream->write(unk_05); //244
		bstream->write(team); //240 //1: blue, 2: yellow
		bstream->write(ready); //241
		bstream->write(weaponCount); //172 //weapon count (not more than 15??)
		for (U32 item : armor)
			bstream->write(item);

		for (U32 item : weaponIds)
			bstream->write(item);

		WriteBuffer(bstream, nickname);
		bstream->write(unk_10); //270
		bstream->write(unk_11); //271
		bstream->write(level); //252
		bstream->write(actionId); //248
		bstream->write(refers); //256
		bstream->write(life); //258
		bstream->write(playerRank); //260 
		bstream->write(experience); //264
		bstream->write(partnerKey); //268
	};
	void unpack(EventConnection * conn, BitStream * bstream) {};
	void process(EventConnection * ps)
	{
	};
	TNL_DECLARE_CLASS(GCJoin);

	wchar_t username[17];
	U32 state; //88 //either 20h, 40h, 80h
	U32 playerId; //92
	U16 characterId; //130
	U32 selectedWeapon; //168
	U32 unk_05; //244
	U8 team; //240 //1: blue, 2: yellow
	U8 ready; //241
	U16 weaponCount; //172 //weapon count (not more than 15??)

	std::array<U32, 9> armor;

	std::array<U32, 4> weaponIds;

	std::string nickname;

	U8 unk_10; //270
	U8 unk_11; //271
	U32 level; //252
	U32 actionId; //248
	U16 refers; //256
	U16 life; //258
	U8 playerRank; //260 
	U32 experience; //264 CURRENT XP APPARENTLY
	U16 partnerKey; //268
};

#endif // !GC_ARRANGED_ACCEPT_HPP