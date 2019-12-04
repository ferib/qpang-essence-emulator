#ifndef ANNOUNCEMENT_EVENT_HPP
#define ANNOUNCEMENT_EVENT_HPP

#include <cstdint>
#include <vector>
#include <string>

#include "string_converter.hpp"
#include "lobby_session.hpp"
#include "lobby.hpp"
#include "request_auth_response_event.hpp"

class AnnouncementEvent : public LobbyPacketEvent {

public:
	AnnouncementEvent() : LobbyPacketEvent(sizeof(Packets::Internal::AnnouncementRsp)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto& packet = pack.Read<Packets::Internal::AnnouncementRsp>();
		session->GetLobby()->Notify(StringConverter::WcharToString(packet.message, 100));	
	}
};

#endif