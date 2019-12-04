#ifndef REQUEST_PLAYER_EQUIPMENT_EVENT_HPP
#define REQUEST_PLAYER_EQUIPMENT_EVENT_HPP

#include <memory>
#include "game_room.hpp"
#include "packet_event.hpp"
#include "connection.hpp"
#include "opcodes.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"

class RequestPlayerEquipmentEvent : public PacketEvent
{
public:
	RequestPlayerEquipmentEvent(const Player::Ptr& player) : m_player(player) {}

	ServerPacket Compose(Connection::Ptr conn)
	{
		Packets::Internal::RequestPlayerEquipment rsp{};
		rsp.playerId = m_player->GetIdentifier();
		rsp.character = m_player->GetCharacter();
		rsp.cmd = 1;

		return ServerPacket::Create<Opcode::ROOM_REQUEST_PLAYER_EQUIPMENT>(rsp);
	}
private:
	Player::Ptr m_player;
};

#endif
