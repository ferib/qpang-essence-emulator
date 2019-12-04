#include "room_packet_handler.hpp"

#include "request_auth_response_event.hpp"
#include "i_am_lobby_event.hpp"
#include "request_player_equipment_response_event.hpp"

RoomPacketHandler::RoomPacketHandler()
{
	_events[Opcode::I_AM_LOBBY] = new IAmLobbyEvent();
	_events[Opcode::ROOM_REQUEST_AUTH_RSP] = new RequestAuthResponseEvent();
	_events[Opcode::ROOM_REQUEST_PLAYER_EQUIPMENT_RSP] = new RequestPlayerEquipmentResponseEvent();
}
