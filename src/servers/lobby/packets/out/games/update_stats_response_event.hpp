#ifndef UPDATE_STATS_RESPONSE_EVENT_HPP
#define UPDATE_STATS_RESPONSE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"

class UpdateStatsResponseEvent : public LobbyPacketEvent {

public:
	UpdateStatsResponseEvent()
	{	
	}

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::UpdatePlayerStats rsp{};

		rsp.don = session->Info()->Don();
		rsp.experience = session->Info()->Experience();
		rsp.coins = session->Info()->Coins();

		return ServerPacket::Create<Opcode::LOBBY_ROOM_REQUEST_STATS_RSP>(rsp);
	}
private:
};

#endif