#ifndef GC_GAME_STATE_HPP
#define GC_GAME_STATE_HPP

#include <vector>


#include "game_net_event.hpp"


class GCGameState : public GameNetEvent
{
	typedef NetEvent Parent;

public:
	GCGameState() : GameNetEvent{ GC_GAME_STATE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {}

	GCGameState(U32 playerId, U32 cmd, const U32 value = 0, const U32 dataUid = 0) : GameNetEvent{ GC_GAME_STATE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		this->uid = playerId;
		this->cmd = cmd;
		this->data = value;
		this->dataUid = dataUid;
	}

	void pack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->write(uid);
		bstream->write(cmd);
		bstream->write(data);
		bstream->write(dataUid);
		bstream->write(gainExp);
		bstream->write(gainDon);
		bstream->write(U8(0));

		for (int i = 0; i < counter; i++)
		{
			bstream->write(U16(1));
		}

		bstream->write(U8(0));

		for (int i = 0; i < mBonusCount; i++)
		{
			bstream->write(U16(1));
			bstream->write(F32(1234));
			bstream->write(F32(2345));
			bstream->write(U8(12));
			bstream->write(U8(1));
		}
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};
	

	struct BonusInfo
	{
		U16 mId;
		F32 mExp;
		F32 mDon;
		U8 mOp;
		U8 mType;
	};

	U32 uid = 0;
	U8 cmd = 0;
	U32 data = 0;
	U32 dataUid = 0;
	U16 gainExp = 0;
	U16 gainDon = 0;

	U8 counter = 0;
	std::vector<U16> unk_01 = {}; //size: mCounter

	U8 mBonusCount = 0;
	//Bonus list
	std::vector<BonusInfo> mBonusList = {}; //size: mBonusCount

	TNL_DECLARE_CLASS(GCGameState);
};

#endif // !GC_ARRANGED_ACCEPT_HPP