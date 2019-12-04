#ifndef CG_MOTION_H
#define CG_MOTION_H

#include "game_net_event.hpp"

class GCMotion;

class CGMotion : public GameNetEvent
{

	typedef NetEvent Parent;
public:
	CGMotion() : GameNetEvent{ CG_MOTION, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&cmd);
		bstream->read(&unk_02);
		bstream->read(&unk_03);
		bstream->read(&unk_04);
		bstream->read(&unk_05);
		bstream->read(&unk_06);
		bstream->read(&unk_07);
		bstream->read(&unk_08);
		bstream->read(&unk_09);
		bstream->read(&playerId);
	};

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
					session->RelayMotion(*this);
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	U32 cmd;
	U32 unk_02;
	U32 unk_03;
	U32 unk_04;
	U32 unk_05;
	U32 unk_06;
	U32 unk_07;
	U32 unk_08;
	U32 unk_09;
	U32 playerId;

	TNL_DECLARE_CLASS(CGMotion);
};
#endif