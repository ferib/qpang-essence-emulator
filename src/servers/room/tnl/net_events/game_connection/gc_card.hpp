#ifndef GC_CARD_HPP
#define GC_CARD_HPP

#include "game_net_event.hpp"
#include "cg_card.hpp"

class GCCard : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCCard() : GameNetEvent{ GC_CARD, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCCard(CGCard card) : GameNetEvent{ GC_CARD, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->uid = card.uid;
		this->targetUid = card.targetUid;
		this->cmd = card.cmd;
		this->cardType = card.cardType;
		this->itemId = card.itemId;
		this->seqId = card.seqId;
	};
	GCCard(uint32_t uid, uint8_t cmd, uint32_t cardType, uint32_t chargePoint, uint32_t skillCount) : GameNetEvent{ GC_CARD, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->uid = uid;
		this->cmd = cmd;
		this->cardType = cardType;
		this->chargePoint = chargePoint;
		this->skillCount = skillCount;
	};
	GCCard(uint32_t uid, uint8_t cmd, uint32_t targetUid, uint32_t itemId, uint32_t seqId, uint32_t cardType, uint32_t chargePoint, uint32_t skillCount) : GameNetEvent{ GC_CARD, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->uid = uid;
		this->cmd = cmd;
		this->targetUid = targetUid;
		this->itemId = itemId;
		this->seqId = seqId;
		this->cardType = cardType;
		this->chargePoint = chargePoint;
		this->skillCount = skillCount;
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(cmd);
		bstream->write(uid);
		bstream->write(targetUid);
		bstream->write(itemId);
		bstream->write(seqId);
		bstream->write(cardType);
		bstream->write(actionType);
		bstream->write(chargePoint);
		bstream->write(skillCount);
		bstream->write(leftCount);
		bstream->write(dataSrcUid);
		bstream->write(dataTrgUid);
		bstream->write(unk_01);
		bstream->write(count);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U8 cmd = 0;
	U32 uid = 0;
	U32 targetUid = 0;
	U32 itemId = 0;
	U64 seqId = 0;
	U32 cardType = 0;
	U32 actionType = 0;
	U32 chargePoint = 0;
	U32 skillCount = 0;
	U32 leftCount = 0;
	U32 dataSrcUid = 0;
	U32 dataTrgUid = 0;
	U32 unk_01 = 0;
	U8 count = 0;

	TNL_DECLARE_CLASS(GCCard);
};

#endif // !GC_ARRANGED_ACCEPT_HPP