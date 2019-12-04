#ifndef RELOAD_LEADERBOARD_HPP
#define RELOAD_LEADERBOARD_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "ranking_response_event.hpp"
#include <vector>
#include "leaderboard.hpp"

class ReloadLeaderboardEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto lobby = session->GetLobby();
		lobby->Ranking()->Load();
		lobby->Notify("Leaderboards are refreshed in-game, check your new rank!");

		std::vector<LobbySession::Ptr> sessions = lobby->Sessions();

		for (auto session : sessions)
		{
			auto rank = lobby->Ranking()->GetRank(session->Info()->Id());
			session->Send(RankingResponseEvent{rank}.Compose(nullptr));
		}
	}
private:
};

#endif