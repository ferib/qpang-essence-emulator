#ifndef GAMEROOMS_EVENT_HPP
#define GAMEROOMS_EVENT_HPP

#include "gameroom.hpp"
#include <vector>
#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "gamerooms_response_event.hpp"

class GameroomsEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::vector<GameRoom> rooms = session->GetLobby()->Rooms()->List();

		session->Send(GameroomsResponseEvent{rooms}.Compose(session));
	}
};

#endif