#ifndef RANKING_EVENT_HPP
#define RANKING_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "ranking_response_event.hpp"
#include <vector>
#include <cstdint>
#include "lobby_session.hpp"
#include "lobby.hpp"
#include "ranking_response_event.hpp"
#include "leaderboard.hpp"

class RankingEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		Leaderboard::Position rank = session->GetLobby()->Ranking()->GetRank(session->Info()->Id());
		session->Send(RankingResponseEvent{ rank }.Compose(session));
	}
};

#endif