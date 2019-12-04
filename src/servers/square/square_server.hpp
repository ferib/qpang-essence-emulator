#ifndef _SQUARE_SERVER_H
#define _SQUARE_SERVER_H

//std
#include <vector>

#include <net/server.hpp>
#include "square_session.hpp"
#include "connector.hpp"
#include "square_manager.hpp"
#include "square_packet_handler.hpp"


class SquareServer : public Server
{
	typedef Server Parent;
public:
	SquareServer();
	void HandleAccept(TcpSocket&& sock);
	void OnConnectorConnected(Connector& socket);
	void Run();



private:
	Logger* _logger;
	SquarePacketHandler* _handler;
	SquareManager _manager;
};



#endif //_SQUARE_SERVER_H