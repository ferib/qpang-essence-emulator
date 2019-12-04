#ifndef AUTH_PACKET_HANDLER_HPP
#define AUTH_PACKET_HANDLER_HPP

#include "packet_handler.hpp"
#include "handshake_event.hpp"
#include "login_event.hpp"
#include "lobby_notify_event.hpp"
#include "i_am_lobby_event.hpp"
#include "opcodes.hpp"

class AuthPacketHandler : public PacketHandler {

public:
	AuthPacketHandler()
	{
		sLogger->Get()->info("AuthPacketHandler: Loading event");
		_events[Opcode::KEY_EXCHANGE] = new HandshakeEvent();
		_events[Opcode::AUTH_LOGIN] = new LoginEvent();
		_events[Opcode::LOBBY_NOTIFY] = new LobbyNotifyEvent();
		_events[Opcode::I_AM_LOBBY] = new IamLobbyEvent();
	};

	~AuthPacketHandler()
	{
		_events.clear();
	};
};

#endif