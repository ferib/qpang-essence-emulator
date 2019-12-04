#ifndef LOBBY_NOTIFY_EVENT_HPP
#define LOBBY_NOTIFY_EVENT_HPP

#include <cstdint>
#include <memory>
#include <array>

#include "lobby_packet_event.hpp"

class LobbyNotifyEvent : public LobbyPacketEvent {

public:
	LobbyNotifyEvent(std::array<uint8_t, 16> uuid) { _uuid = uuid; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Auth::LobbyNotify lobbyNotify{};
		lobbyNotify.uuid = _uuid;
		return ServerPacket::Create<Opcode::LOBBY_NOTIFY>(lobbyNotify);
	};
private:
	std::array<uint8_t, 16> _uuid;
};

#endif