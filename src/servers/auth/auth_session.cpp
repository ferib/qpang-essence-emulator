#include "auth_session.hpp"
#include <packets/packet_data.hpp>

AuthSession::AuthSession(Connection::Ptr connection) : Session{ connection }
{
	_connection->SetHandlers(
		std::bind(&AuthSession::HandlePacket, this, std::placeholders::_1),
		std::bind(&AuthSession::HandleClose, this));
}

void AuthSession::HandlePacket(ClientPacket& packet)
{
	if(_connection->state == Connection::State::CONNECTED)
		handler->Execute(_connection, packet);
}

void AuthSession::HandleClose()
{
	//
}