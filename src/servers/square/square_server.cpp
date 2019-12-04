#include "square_server.hpp"
#include "packet_data.hpp"
#include "i_am_square_event.hpp"


SquareServer::SquareServer()
{
	_handler = new SquarePacketHandler();
}

void SquareServer::HandleAccept(TcpSocket&& sock)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(sock));
	auto session = std::make_shared<SquareSession>(conn);

	session->handler = _handler;
	session->SetManager(&_manager);
	_manager.AddSession(session);
	session->StartNetworking();
}

void SquareServer::OnConnectorConnected(Connector& connector)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(*connector.getSocket()));
	conn->SendPacket(IAmSquareEvent{}.Compose(conn), BlowfishContext::CryptoType::PUBLIC);
	conn->SetEncryption(false);
	_manager.SetLobbyServer(conn);
	Parent::Run();
}

void SquareServer::Run()
{
	Connector c{ "127.0.0.1", 8005 , std::bind(&SquareServer::OnConnectorConnected, this, std::placeholders::_1)};
	c.Connect();
}