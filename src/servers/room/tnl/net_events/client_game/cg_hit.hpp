#ifndef CG_HIT_H
#define CG_HIT_H

#include "game_net_event.hpp"
#include "game.hpp"
#include "weapon.hpp"

class CGHit : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	enum HitLocation : U8 {
		HEAD = 0,
		BODY = 1,
		R_ARM = 2,
		R_HAND = 3,
		L_ARM = 4,
		L_HAND = 5,
		R_LEG = 6,
		R_FEET = 7,
		L_LEG = 8,
		L_FEET = 9
	};

	enum MapObject : U8 {
		TRAP_FLAME = 1,
		TRAP_PRESS = 2,
		TRAP_FALL = 3,
		TRAP_DOWN = 4,
		TRAP_JELLY_JUMP = 5,
		TRAP_POISON_GROUND = 6,
		TRAP_SHIP_PROPELLER = 7
	};

	/*
	Values:
	1
	3
	5
	2 (Environmental)
	6
	7 (NPC hit)
	8 (NPC Attack)
	9 (Move hack)
	10 (Move gap)

	Other values: player hit
	*/


	CGHit() : GameNetEvent{ CG_HIT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&srcPlayerId);
		bstream->read(&dstPlayerId);
		bstream->read(&unk_03);
		bstream->read(&srcPosX);
		bstream->read(&srcPosY);
		bstream->read(&srcPosZ);
		bstream->read(&dstPosX);
		bstream->read(&dstPosY);
		bstream->read(&dstPosZ);
		bstream->read(&count);
		bstream->read(&hitType);
		bstream->read(&hitLocation);
		bstream->read(&weaponId);
		bstream->read(&rtt);
		bstream->read(&weaponType);
		bstream->read(&unk_16);
		bstream->read(&unk_17);
		bstream->read(&unk_18);
	};

	void handle(Player::Ptr player)
	{


	}

	void process(EventConnection* ps)
	{
		auto player = sGame->FindPlayer(ps);

		if (player != nullptr)
		{
			auto session = player->GetSession();
			auto room = player->GetRoom();

			if (session != nullptr && room != nullptr)
			{
				const uint32_t sourceIdentifier = srcPlayerId;
				const uint32_t targetIdentifier = dstPlayerId;

				uint16_t damage = 0;

				if (sourceIdentifier == targetIdentifier)
				{
					switch (weaponId)
					{
					case TRAP_FLAME:
					case TRAP_POISON_GROUND:
					case TRAP_SHIP_PROPELLER:
						damage = 10;
						break;
					case TRAP_PRESS:
						damage = 150;
						break;
					case TRAP_FALL:
						damage = 9999;
						break;
					case TRAP_DOWN: // fall damage
					case TRAP_JELLY_JUMP:
						damage = 0;
						break;
					}

					session->DepleteHealth(damage);

					player->GetConnection()->TakeDamage(*this, damage, session->GetHealth());

					if (session->GetHealth() == 0)
					{
						auto roomSession = room->GetSession();
						if (roomSession != nullptr)
						{
							roomSession->KillPlayer(player, player, weaponId, false);
						}
					}
				}

				if (srcPlayerId != dstPlayerId && session->HasWeapon(weaponId))
				{
					auto target = sGame->FindPlayer(targetIdentifier);

					if (target != nullptr)
					{

							auto targetSession = target->GetSession();
							auto roomSession = room->GetSession();

							if (roomSession != nullptr && targetSession != nullptr)
							{
								if (session->HasWeapon(weaponId))
								{
									// TODO: Effects

									uint16_t baseDamage = sGame->Weapons().GetDamage(weaponId);

									switch (hitLocation)
									{
									case HEAD:
										baseDamage *= 1;
										break;
									case BODY:
										baseDamage *= 0.9;
										break;
									case L_LEG:
									case R_LEG:
									case L_ARM:
									case R_ARM:
										baseDamage *= 0.8;
										break;
									case L_FEET:
									case R_FEET:
									case L_HAND:
									case R_HAND:
										baseDamage *= 0.6;
										break;
									}

									damage = targetSession->IsInvincible() ? 0 : baseDamage;

									if (room->GetMode()->IsTeamMode() && target->GetTeam() == player->GetTeam())
									{
										damage = 0;
									}

									if (targetSession->GetHealth() > 0)
									{
										targetSession->DepleteHealth(damage);
									}

									if (targetSession->GetHealth() == 0)
									{
										roomSession->KillPlayer(player, target, weaponId, hitLocation == HitLocation::HEAD);
									}

									roomSession->RelayHit(*this, damage, targetSession->GetHealth(), session->GetStreak());
								}
						}
					}
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	U32 srcPlayerId; //140
	U32 dstPlayerId; //144
	U32 unk_03; //88
	F32 srcPosX; //116
	F32 srcPosY; //120
	F32 srcPosZ; //124
	F32 dstPosX; //128
	F32 dstPosY; //132
	F32 dstPosZ; //136
	U32 count; //92
	U8 hitType; //148 
	U8 hitLocation; //149

	U32 weaponId; //96
	U64 rtt; //104
	U8 weaponType; //112
	U8 unk_16; //150
	U8 unk_17; //151
	U32 unk_18; //152

	TNL_DECLARE_CLASS(CGHit);
};
#endif