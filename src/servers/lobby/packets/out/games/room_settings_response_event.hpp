#ifndef ROOM_SETTING_RESPONSE_EVENT_HPP
#define ROOM_SETTING_RESPONSE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"

class RoomSettingsResponseEvent : public LobbyPacketEvent {

public:
	RoomSettingsResponseEvent(uint32_t host, uint32_t port, bool roomsAvailable)
	{
		_host = host;
		_port = port;
		_roomsAvailable = roomsAvailable;
	}

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::GameRefreshRsp rsp{};
		rsp.gameServerIp = _host;
		rsp.gameServerPort = _port;
		rsp.canCreateRooms = _roomsAvailable;
		return ServerPacket::Create<Opcode::LOBBY_GAMESERVER_REFRESH_RSP>(rsp);
	}
private:
	uint32_t _host;
	uint16_t _port;
	bool _roomsAvailable;
};

#endif