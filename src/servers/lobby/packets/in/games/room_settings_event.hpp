#ifndef ROOM_SETTING_EVENT_HPP
#define ROOM_SETTING_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "room_settings_response_event.hpp"
#include "boost/lexical_cast.hpp"
#include "settings_manager.hpp"
#include "gamerooms_response_event.hpp"

class RoomSettingsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::string strHost = sSettings->GetSetting("room_host");
		std::string strPort = sSettings->GetSetting("room_port");

		uint32_t host = inet_addr(strHost.c_str());
		uint16_t port = boost::lexical_cast<uint16_t>(strPort);
		bool roomsAvailable = true; // for now.

		auto rooms = session->GetLobby()->Rooms()->List();

		session->Send(GameroomsResponseEvent{ rooms }.Compose(session));
		session->Send(RoomSettingsResponseEvent{ host, port, roomsAvailable }.Compose(session));
	}
};

#endif