#ifndef UPDATE_STATS_EVENT_HPP
#define UPDATE_STATS_EVENT_HPP

#include <string>
#include <memory>
#include <cstdint>
#include <boost/format.hpp>
#include "lobby_packet_event.hpp"
#include "update_level_event.hpp"

class UpdateStatsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		if (session == nullptr)
			return;

		sLogger->Get()->debug("Update stats event");

		uint32_t oldLevel = session->Info()->Level();

		sLogger->Get()->debug("Old level: {0:d}", oldLevel);

		sLogger->Get()->debug("UID: {0:d}", session->Info()->Uid());

		//session->Info()->Load(session->Info()->Uid());

		uint32_t newLevel = session->Info()->Level();

		sLogger->Get()->debug("UpdateStatsEvent Sending Response");

		session->Send(UpdateStatsResponseEvent{}.Compose(session));
		session->Send(CashResponseEvent{ session->Info()->Cash() }.Compose(session));

		if (oldLevel != newLevel)
		{
			session->GetLobby()->Notify(str(boost::format("Player %1% leveled up to level %2%, congratulations!") % session->Info()->Nickname() % newLevel));
			session->GetLobby()->GetSquare()->SendPacket(UpdateLevelEvent{ session->Info()->Id(), session->Info()->Level() }.Compose(session));
		}

		sLogger->Get()->debug("Idk");
	}
};

#endif