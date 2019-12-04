#ifndef CG_WEAPON_H
#define CG_WEAPON_H

#include "game_net_event.hpp"

class CGWeapon : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	enum CMD : U32
	{
		SWAP = 0,
		RELOAD = 3,
		ENABLE_SHOOTING = 5,
	};

	CGWeapon() : GameNetEvent{ CG_WEAPON, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirClientToServer } {};

	void pack(EventConnection* conn, BitStream* bstream) {};
	void unpack(EventConnection* conn, BitStream* bstream)
	{
		bstream->read(&playerId);
		bstream->read(&cmd);
		bstream->read(&itemId);
		bstream->read(&cardId);
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
					if (cmd == CMD::SWAP)
					{
						auto playerSession = player->GetSession();

						if (playerSession != nullptr)
						{
							if (playerSession->HasWeapon(itemId))
							{
								playerSession->SetWeapon(itemId);

								session->RelayWeapon(*this);
								player->GetConnection()->EnableShooting(player);
							}
						}
					}

					if (cmd == CMD::RELOAD)
					{
						session->RelayWeapon(*this);
					}
				}
			}
		}

		NET_POST_EVENT(ps);
	};

	U32 playerId;
	U32 cmd;
	U32 itemId;
	U64 cardId;

	TNL_DECLARE_CLASS(CGWeapon);
};
#endif