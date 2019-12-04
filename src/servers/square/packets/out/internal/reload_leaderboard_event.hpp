#ifndef RELOAD_LEADERBOARD_EVENT_HPP
#define RELOAD_LEADERBOARD_EVENT_HPP

#include <cstdint>
#include "packet_event.hpp"
#include "packet_data.hpp"

class ReloadLeaderboardEvent : public PacketEvent {

public:
	ServerPacket Compose(Connection::Ptr session) override
	{
		return ServerPacket::Create<Opcode::RELOAD_LEADERBOARD_COMMAND>(Packets::Handshake::KeyExchange{});
	}
};

#endif