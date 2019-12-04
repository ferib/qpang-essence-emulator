#ifndef NEW_GAMEROOM_EVENT_HPP
#define NEW_GAMEROOM_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "string_converter.hpp"

class UpdateGameRoomEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Internal::UpdateGameRoom>();
		auto lobby = session->GetLobby();

		if (lobby)
			lobby->Rooms()->UpdateRoom(packet.id, StringConverter::WcharToString(packet.name, 30), packet.map, packet.mode, packet.currPlayers, packet.maxPlayers, packet.meleeOnly, packet.state);
	}
private:
};

#endif