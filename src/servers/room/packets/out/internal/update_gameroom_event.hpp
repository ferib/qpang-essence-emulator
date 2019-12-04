#ifndef NEW_GAMEROOM_EVENT_HPP
#define NEW_GAMEROOM_EVENT_HPP

#include <memory>
#include "game_room.hpp"
#include "packet_event.hpp"
#include "connection.hpp"
#include "opcodes.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"

class UpdateGameRoomEvent : public PacketEvent
{
public:
	UpdateGameRoomEvent(GameRoom::Ptr room) { 
		m_identifier = room->GetIdentifier();
		m_map = room->GetMap();
		m_melee = false;
		m_currentPlayers = room->GetPlayerCount();
		m_maxPlayers = room->GetMaxPlayerCount();
		m_modeIdentifier = room->GetMode()->GetModeIdentifier();
		m_state = room->GetState();
		m_name = room->GetName();
	};

	ServerPacket Compose(Connection::Ptr conn)
	{
		Packets::Internal::UpdateGameRoom rsp{};
		rsp.id = m_identifier;
		rsp.map = m_map;
		wcscpy(rsp.name, L"room");
		rsp.meleeOnly = m_melee;
		rsp.currPlayers = m_currentPlayers;
		rsp.maxPlayers = m_maxPlayers;
		rsp.mode = m_modeIdentifier;
		rsp.state = m_state;
		
		return ServerPacket::Create<Opcode::UPDATE_GAMEROOM>(rsp);
	}
private:
	uint32_t m_identifier;
	uint8_t m_map;
	uint8_t m_melee;
	uint8_t m_currentPlayers;
	uint8_t m_maxPlayers;
	uint8_t m_modeIdentifier;
	uint8_t m_state;
	std::string m_name;
};

#endif // !NEW_GAMEROOM_EVENT_HPP
