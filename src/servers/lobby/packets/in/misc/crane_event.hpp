#ifndef CRANE_EVENT_HPP
#define CRANE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "inventory_manager.hpp"
#include "crane_manager.hpp"
#include "inventory_card.hpp"
#include "crane_response_event.hpp"

class CraneEvent : public LobbyPacketEvent {

	enum Error {
		CRANE_FAIL_INVEN_FULL = 362,
		CRANE_FAIL_LACK_COIN = 878,
		CRANE_FAIL_FREQUENCY = 879,
		CRANE_FAIL_SYSTEM_ERROR = 880,
	};

	enum Coin {
		BRONZE = 1,
		SILVER = 10,
		GOLD = 100,
	};

public:
	CraneEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::UseCrane)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::UseCrane>();

		if (packet.times >= 7) // 7 dc's client?
			return session->SendError<Opcode::LOBBY_USE_CRAIN_FAIL>(Error::CRANE_FAIL_FREQUENCY);

		uint32_t coinsCost = Coin::GOLD;

		switch (packet.times)
		{
		case 1:
			coinsCost = 2 * Coin::GOLD;
			break;
		case 3:
			coinsCost = 5 * Coin::GOLD;
			break;
		case 7:
			coinsCost = 12 * Coin::GOLD;
			break;
		default:
			break;
		}

		bool hasEnoughCoins = session->Info()->Coins() >= coinsCost;
		if (!hasEnoughCoins)
			return session->SendError<Opcode::LOBBY_USE_CRAIN_FAIL>(Error::CRANE_FAIL_LACK_COIN);

		if (session->Inventory()->List().size() + packet.times > 199) // max inv size
			return session->SendError<Opcode::LOBBY_USE_CRAIN_FAIL>(Error::CRANE_FAIL_INVEN_FULL);

		session->Info()->Coins(session->Info()->Coins() - coinsCost);
		std::vector<InventoryCard> items;
		for (size_t i = 0; i < packet.times; i++)
		{
			CraneItem item = session->GetLobby()->Crane()->Use();
			if (item.id != NULL)
				items.push_back(session->Inventory()->AddItem(InventoryCard{ session->Info()->Id(), 0, item.itemId, item.period, item.periodType, item.itemType, 1, 1, 0, 0, 0 }));
			else
				return session->SendError<Opcode::LOBBY_USE_CRAIN_FAIL>(Error::CRANE_FAIL_SYSTEM_ERROR);
		}
		session->Send(CraneResponseEvent{ items, session->Info()->Coins() , session->Info()->Don() }.Compose(session));
	}
};

#endif