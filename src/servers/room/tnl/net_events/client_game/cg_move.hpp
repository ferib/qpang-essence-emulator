#ifndef CG_MOVE_H
#define CG_MOVE_H

#include "game_net_event.hpp"
#include "game.hpp"

class CGMove : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	CGMove() : GameNetEvent{ CG_MOVE, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirClientToServer } {};
	U32 playerId;
	U32 cmd;
	U32 unk_01;
	U32 unk_02;
	U32 unk_03;
	U32 unk_04;
	U32 unk_05;
	U32 unk_06;
	U32 unk_07;
	U32 unk_08;
	U32 unk_09;
	U32 unk_10;
	U32 unk_11 = 1;

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&cmd);
		bstream->read(&unk_01);
		bstream->read(&unk_02);
		bstream->read(&unk_03);
		bstream->read(&unk_04);
		bstream->read(&unk_05);
		bstream->read(&unk_06);
		bstream->read(&unk_07);
		bstream->read(&unk_08);
		bstream->read(&unk_09);
		bstream->read(&unk_10);
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
					session->RelayMove(*this);
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	TNL_DECLARE_CLASS(CGMove);
};
#endif