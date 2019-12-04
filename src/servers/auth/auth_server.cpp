#include "auth_server.hpp"
#include "i_am_auth_event.hpp"

void AuthServer::HandleAccept(TcpSocket&& sock)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(sock));
	auto session = std::make_shared<AuthSession>(conn);

	//TODO: Move this to a better spot.
	session->handler = _handler;

	_sessions.push_back(session);
	session->StartNetworking();
}

void AuthServer::OnConnectorConnected(Connector& connector)
{
	if (!connector.isConnected())
		return;

	//There will only be one connector.. this one is the lobbyserver
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(*connector.getSocket()));
	conn->SendPacket(IAmAuthEvent{}.Compose(conn), BlowfishContext::CryptoType::PUBLIC);
	conn->SetEncryption(false);
	AuthManager::Instance()->SetLobbyServer(conn);
	Parent::Run();
}

void AuthServer::Run()
{
	for (Connector* connector : connectors)
	{
		connector->Connect();
	}
}