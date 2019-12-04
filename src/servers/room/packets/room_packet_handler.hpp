#ifndef ROOM_PACKET_HANDLER_HPP
#define ROOM_PACKET_HANDLER_HPP

#include <map>
#include <memory>
#include <string>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "room_packet_event.hpp"
#include "packet_handler.hpp"
#include "opcodes.hpp"

//This packet handler mainly used for internal communication between servers

class RoomPacketHandler : public PacketHandler {

public:
	RoomPacketHandler();

	void Execute(GameLobbySession* session, ClientPacket& pack)
	{
		sLogger->Get()->info("RoomPacketHandler: Executing packet");
		if (_events.size() <= 0)
			return;

		auto theEvent = _events.find(pack.ReadPayloadHeader().opcode);
		if (theEvent != _events.cend())
			return theEvent->second->Read(session, pack);
	}

private:
	std::map<Opcode, RoomPacketEvent*> _events;
	
};

#endif