#include "lobby_server.hpp"
#include "i_am_lobby_event.hpp"
#include "i_am_room_event.hpp"
#include "lobby.hpp"

void LobbyServer::HandleAccept(TcpSocket&& sock)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(sock));
	auto session = std::make_shared<LobbySession>(conn);

	session->handler = _packetHandler;
	session->SetLobby(_lobby);
	_lobby->AddSession(session);
}

void LobbyServer::OnAuthServerConnected(Connector& authConnector)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(*authConnector.getSocket()));
	conn->SendPacket(IAmLobbyEvent{}.Compose(conn), BlowfishContext::CryptoType::PUBLIC);
	conn->SetEncryption(false);
	_lobby->SetAuthServer(conn);
}

void LobbyServer::OnSquareServerConnected(Connector& squareConnector)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(*squareConnector.getSocket()));
	conn->SendPacket(IAmLobbyEvent{}.Compose(conn), BlowfishContext::CryptoType::PUBLIC);
	conn->SetEncryption(false);
	_lobby->SetSquareServer(conn);
}

void LobbyServer::OnRoomServerConnected(Connector& squareConnector)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(*squareConnector.getSocket()));
	conn->SendPacket(IAmLobbyEvent{}.Compose(conn), BlowfishContext::CryptoType::PUBLIC);
	conn->SetEncryption(false);
	_lobby->SetRoomServer(conn);
}

void LobbyServer::Run()
{
	for (Connector* connector : connectors)
	{
		connector->Connect();
	}

	Parent::Run();
}

