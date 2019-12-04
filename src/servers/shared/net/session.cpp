#include "session.hpp"

Session::Session(Connection::Ptr connection)
	: _connection{ connection }
{

}

void Session::StartNetworking()
{
	sLogger->Get()->debug("Start networking");

	_connection->Read();
}

void Session::Send(ServerPacket packet,
	BlowfishContext::CryptoType crypto)
{
	_connection->SendPacket(packet, crypto);
}

void Session::Disconnect()
{
	_connection->Close();
}