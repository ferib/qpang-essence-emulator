#ifndef GC_HIT_HPP
#define GC_HIT_HPP

#include "game_net_event.hpp"
#include "cg_hit.hpp"

class GCHit : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCHit() : GameNetEvent{ GC_HIT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCHit(CGHit &hit, U16 healthLeft, U16 damageDealt, U8 weaponEffect = 0, U8 killCombo = 0) : GameNetEvent{ GC_HIT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->srcPlayerId = hit.srcPlayerId;
		this->dstPlayerId = hit.dstPlayerId;
		this->unk_03 = hit.unk_03;
		this->srcPosX = hit.srcPosX;
		this->srcPosY = hit.srcPosY;
		this->srcPosZ = hit.srcPosZ;
		this->dstPosX = hit.dstPosX;
		this->dstPosY = hit.dstPosY;
		this->dstPosZ = hit.dstPosZ;
		this->count = hit.count;
		this->hitType = hit.hitType;
		this->hitLocation = hit.hitLocation;
		this->healthLeft = healthLeft;
		this->damageDealt = damageDealt;
		this->weaponId = hit.weaponId;
		this->rtt = hit.rtt;
		this->weaponType = hit.weaponType;
		this->unk_16 = hit.unk_16;
		this->killCombo = killCombo;
		this->unk_18 = hit.unk_18;
		this->weaponEffect = weaponEffect;
		this->unk_20 = 0;
		this->unk_21 = 0;
		this->unk_22 = 0;
	};
	GCHit(U32 playerId, U16 damageDealt, U16 healthLeft) : GameNetEvent{ GC_HIT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->srcPlayerId = playerId;
		this->dstPlayerId = playerId;
		this->healthLeft = healthLeft;
		this->damageDealt = damageDealt;
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(srcPlayerId);
		bstream->write(dstPlayerId);
		bstream->write(unk_03);
		bstream->write(srcPosX);
		bstream->write(srcPosY);
		bstream->write(srcPosZ);
		bstream->write(dstPosX);
		bstream->write(dstPosY);
		bstream->write(dstPosZ);
		bstream->write(count);
		bstream->write(hitType);
		bstream->write(hitLocation);
		bstream->write(healthLeft);
		bstream->write(damageDealt);
		bstream->write(weaponId);
		bstream->write(rtt);
		bstream->write(weaponType);
		bstream->write(unk_16);
		bstream->write(killCombo);
		bstream->write(unk_18);
		bstream->write(weaponEffect);
		bstream->write(unk_20);
		bstream->write(unk_21);
		bstream->write(unk_22);
		bstream->writeFlag(true); // Not sure what this is, but it needs it. What does it do with the value?
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 srcPlayerId;
	U32 dstPlayerId;
	U32 unk_03;
	F32 srcPosX;
	F32 srcPosY;
	F32 srcPosZ;
	F32 dstPosX;
	F32 dstPosY;
	F32 dstPosZ;
	U32 count; //??
	U8 hitType;
	U8 hitLocation;
	U16 healthLeft;
	U16 damageDealt;
	U32 weaponId;
	U64 rtt;
	U32 weaponType;
	U8 unk_16;
	U8 killCombo;
	U8 unk_18;
	U8 weaponEffect; // debuff
	U8 unk_20;
	U8 unk_21;
	U32 unk_22;

	TNL_DECLARE_CLASS(GCHit);
};

#endif // !GC_ARRANGED_ACCEPT_HPP