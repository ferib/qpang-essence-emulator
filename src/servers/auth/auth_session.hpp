#ifndef _AUTH_SESSION_H
#define _AUTH_SESSION_H

#include <net/session.hpp>
#include "auth_packet_handler.hpp"

class AuthSession : public Session
{

public:	
	using Ptr = std::shared_ptr<AuthSession>;
	AuthSession(Connection::Ptr connection);
	void HandlePacket(ClientPacket& packet);
	void HandleClose();

	AuthPacketHandler* handler;
};

#endif //_AUTH_SESSION_H