#ifndef EQUIPPED_SKILL_CARDS_RESPONSE_EVENT_HPP
#define EQUIPPED_SKILL_CARDS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <array>
#include <cstdint>
#include "equipment_manager.hpp"
#include "lobby_session.hpp"
#include "inventory_card.hpp"

class EquippedSkillCardsResponseEvent : public LobbyPacketEvent {

public:
	EquippedSkillCardsResponseEvent(std::array<std::array<uint32_t, 3>, 6> skillCards) { _skillCards = skillCards; };

	ServerPacket Compose(LobbySession* session) override 
	{
		Packets::Lobby::EquippedSkillCardsRsp rsp{};

		std::array<uint32_t, 3> skillCards = _skillCards[session->Equipment()->GetCharacterIndex(session->Info()->Character())];
		for (size_t i = 0; i < 3; i++)
		{
			Packets::Lobby::InventoryCardsRsp::Card card;
			InventoryCard inventoryCard = session->Inventory()->GetItemByCardId(skillCards[i]);

			card.cardId = inventoryCard.id;
			card.itemId = inventoryCard.itemId;
			card.unknown01 = 0xA;
			card.unknown02 = 0xA;
			card.unknown03 = 0xA;
			card.unknown04 = 2;
			card.opened = inventoryCard.opened;
			card.giftable = inventoryCard.giftable;
			card.isBoosted = inventoryCard.boosted;
			card.boostLevel = inventoryCard.boostLevel;
			card.hidden = false; // ?
			card.unknown04 = false;
			card.unknown05 = true;
			card.unknown06 = true;
			card.dateReceived = inventoryCard.timeCreated;
			rsp.card[i] = card;
		}

		return ServerPacket::Create<Opcode::LOBBY_EQUIPPED_SKILS_RSP>(rsp);
	};
private:
	std::array<std::array<uint32_t, 3>, 6> _skillCards;
};

#endif