#ifndef _AUTH_SERVER_H
#define _AUTH_SERVER_H

//std
#include <vector>
#include <array>

#include "auth_session.hpp"
#include <net/server.hpp>

#include "connector.hpp"
#include "auth_manager.hpp"
#include "auth_packet_handler.hpp"

class AuthServer : public Server
{
	typedef Server Parent;

public:
	void HandleAccept(TcpSocket&& sock);
	void OnConnectorConnected(Connector& connector);
	void Run();
	std::vector<std::shared_ptr<AuthSession>> _sessions;
	std::array<Connector*, 1> connectors = {
		new Connector(sSettings->GetSetting("lobby_host"), 8005, std::bind(&AuthServer::OnConnectorConnected, this, std::placeholders::_1))
	};

private:
	AuthPacketHandler* _handler = new AuthPacketHandler();
};



#endif //_AUTH_SERVER_H