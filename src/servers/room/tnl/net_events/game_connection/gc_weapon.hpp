#ifndef GC_WEAPON_HPP
#define GC_WEAPON_HPP

#include "game_net_event.hpp"

#include "cg_weapon.hpp"

class GCWeapon : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	GCWeapon() : GameNetEvent{ GC_WEAPON, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCWeapon(CGWeapon& weapon) : GameNetEvent{ GC_WEAPON, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->playerId = weapon.playerId;
		this->cmd = weapon.cmd;
		this->weaponId = weapon.itemId;
		this->weaponSeqId = weapon.cardId;
		this->weaponOpt = weaponOpt;
	};

	GCWeapon(U32 playerId, U32 cmd, U16 weaponOpt = 0) : GameNetEvent{ GC_WEAPON, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->playerId = playerId;
		this->cmd = cmd;
		this->weaponOpt = weaponOpt;
	};

	U32 playerId = 0;
	U32 cmd = 100;	
	U32 weaponId = 0;
	U64 weaponSeqId = 0;
	U16 weaponOpt = 0; // certain types.. poison, freeze, stun etc.
	U8 outOfBullet = false;
	U16 magazineId = 75;

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(playerId);
		bstream->write(cmd); // 0 = switch, 1 = gun at ground zero??, 3 = reload
		bstream->write(weaponId);
		bstream->write(weaponSeqId);
		bstream->write(weaponOpt);
		bstream->write(outOfBullet);
		bstream->write(magazineId); // 75 or 76??
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};
	TNL_DECLARE_CLASS(GCWeapon);
};

#endif // !GC_ARRANGED_ACCEPT_HPP