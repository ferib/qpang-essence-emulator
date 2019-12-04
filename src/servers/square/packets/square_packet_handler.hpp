#ifndef SQUARE_PACKET_HANDLER_HPP
#define SQUARE_PACKET_HANDLER_HPP

//std
#include <map>
#include "opcodes.hpp"
#include "square_packet_event.hpp"
#include "packet_handler.hpp"

//OUR EVENTS
#include "i_am_lobby_event.hpp"
#include "handshake_event.hpp"
#include "login_event.hpp"
#include "request_equipment_response_event.hpp"
#include "join_event.hpp"
#include "player_join_event.hpp"
#include "move_event.hpp"
#include "chat_event.hpp"
#include "update_player_event.hpp"
#include "emote_event.hpp"
#include "join_back_event.hpp"
#include "start_tutorial_event.hpp"
#include "update_level_event.hpp"
//END EVENTS

class SquareSession;

class SquarePacketHandler : public PacketHandler {

public:

	SquarePacketHandler()
	{
		_events[Opcode::I_AM_LOBBY] = new IAmLobbyEvent();
		_events[Opcode::KEY_EXCHANGE] = new HandshakeEvent();
		_events[Opcode::SQUARE_LOGIN] = new LoginEvent();
		_events[Opcode::REQUEST_EQUIPMENT_RSP] = new RequestEquipmentResponseEvent();
		_events[Opcode::SQUARE_JOIN_PARK] = new JoinEvent();
		_events[Opcode::SQUARE_PLAYER_JOIN] = new PlayerJoinEvent();
		_events[Opcode::SQUARE_PLAYER_MOVE] = new MoveEvent();
		_events[Opcode::SQUARE_CHAT] = new ChatEvent();
		_events[Opcode::SQUARE_PLAYER_UPDATE] = new UpdatePlayerEvent();
		_events[Opcode::SQUARE_PLAYER_EMOTE] = new EmoteEvent();
		_events[Opcode::SQUARE_JOIN_BACK] = new JoinBackEvent();
		_events[Opcode::SQUARE_START_TUTORIAL] = new StartTutorialEvent();
		_events[Opcode::UPDATE_PLAYER_LEVEL] = new UpdateLevelEvent();
	}

	void Execute(SquareSession* session, ClientPacket& pack)
	{
		if (_events.size() <= 0)
			return;

		auto header = pack.ReadPayloadHeader();
		auto theEvent = _events.find(header.opcode);

		if (theEvent != _events.cend())
		{
			if (theEvent->second->size == 0 || header.length == theEvent->second->size)
			{
				try
				{
					sLogger->Get()->debug("{0} Packet {1:d}", session->Info()->Nickname(), static_cast<uint16_t>(header.opcode));
					return theEvent->second->Read(session, pack);
				}
				catch(std::exception& e)
				{
					sLogger->Get()->error("SquarePacketHandler Execution error: {0}", e.what());
				}
			}
		}
	}

private:
	std::map<Opcode, SquarePacketEvent*> _events;
};

#endif