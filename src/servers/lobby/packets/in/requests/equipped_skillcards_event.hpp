#ifndef EQUIPPED_SKILL_CARDS_EVENT_HPP
#define EQUIPPED_SKILL_CARDS_EVENT_HPP

#include "lobby_packet_event.hpp"
#include <array>
#include <cstdint>
#include "lobby_session.hpp"
#include "equipment_manager.hpp"
#include "leaderboard.hpp"
#include "equipped_skillcards_response_event.hpp"

class EquippedSkillCardsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::array<std::array<uint32_t, 3>, 6> skillCards = session->Equipment()->GetSkillCards();
		session->Send(EquippedSkillCardsResponseEvent{ skillCards }.Compose(session));
	}
};

#endif