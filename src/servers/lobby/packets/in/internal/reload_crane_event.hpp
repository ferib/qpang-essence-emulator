#ifndef RELOAD_CRANE_EVENT_HPP
#define RELOAD_CRANE_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include <vector>
#include "whisper_response_event.hpp"
#include "crane_item.hpp"

class ReloadCraneEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto lobby = session->GetLobby();
		lobby->Crane()->Load();
		lobby->Notify("There are new items in the crane, check them out!");
	}
private:
};

#endif