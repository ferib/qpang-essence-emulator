#ifndef CG_CARD_HPP
#define CG_CARD_HPP

#include "game_net_event.hpp"
class CGCard : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	enum CMD : U32
	{
		ABILITY = 0x04,
	};

	CGCard() : GameNetEvent{ CG_CARD, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&uid);
		bstream->read(&targetUid);
		bstream->read(&cmd);
		bstream->read(&cardType);
		bstream->read(&itemId);
		bstream->read(&seqId);
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
					if (cmd == CMD::ABILITY)
					{
						session->RelayAbility(*this);
					}
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	U32 uid;
	U32 targetUid;
	U32 cmd;
	U32 cardType;
	U32 itemId;
	U64 seqId;

	TNL_DECLARE_CLASS(CGCard);
};
#endif