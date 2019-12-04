#ifndef RANKING_RESPONSE_EVENT_HPP
#define RANKING_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "opcodes.hpp"
#include "leaderboard.hpp"

class RankingResponseEvent : public LobbyPacketEvent {

public:
	RankingResponseEvent(Leaderboard::Position rank) { _rank = rank; };

	ServerPacket Compose(LobbySession* session) override 
	{
		Packets::Lobby::PlayerRankingRsp rsp{};
		rsp.rank = _rank.rank;
		rsp.amount = _rank.difference;
		return ServerPacket::Create<Opcode::LOBBY_PLAYER_RANKING_RSP>(rsp);
	};
private:
	Leaderboard::Position _rank;
};

#endif