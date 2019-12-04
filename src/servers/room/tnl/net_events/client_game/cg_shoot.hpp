#ifndef CG_SHOOT_H
#define CG_SHOOT_H

#include "game_net_event.hpp"

class GCShoot;

class CGShoot : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGShoot() : GameNetEvent{ CG_SHOOT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	U32 playerId;
	F32 unk_02;
	F32 unk_03;
	F32 unk_04;
	F32 unk_05;
	F32 unk_06;
	F32 unk_07;
	F32 unk_08;
	F32 unk_09;
	F32 unk_10;
	U32 itemId;
	U64 cardId;
	U16 cmd;
	U32 unk_11;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&unk_02);
		bstream->read(&unk_03);
		bstream->read(&unk_04);
		bstream->read(&unk_05);
		bstream->read(&unk_06);
		bstream->read(&unk_07);
		bstream->read(&unk_08);
		bstream->read(&unk_09);
		bstream->read(&unk_10);
		bstream->read(&itemId);
		bstream->read(&cardId);
		bstream->read(&cmd);
		bstream->read(&unk_11);
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
				auto session = room->GetSession();

				if (session != nullptr)
				{
					session->RelayShoot(*this);
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGShoot);
};
#endif