#ifndef _SESSION_H
#define _SESSION_H

#include "connection.hpp"
#include "packets/packet.hpp"
#include <boost/thread.hpp>

class Session
{
	//nothing much for now... will be useful later for common data
public:
	Session(Connection::Ptr connection);

	//terrible terrible function name...
	void StartNetworking();

	void Send(ServerPacket packet, 
		BlowfishContext::CryptoType crypto = BlowfishContext::CryptoType::AUTHENTICATED);

	template<Opcode Op>
	void SendError(uint16_t errCode,
		BlowfishContext::CryptoType crypto = BlowfishContext::CryptoType::AUTHENTICATED)
	{
		auto packet = ServerPacket::CreateErrorPacket<Op>(errCode);
		Send(packet, crypto);
	}
	void Disconnect();
	inline Connection::Ptr GetConnection() { return _connection; };
protected:
	Connection::Ptr _connection;
	boost::thread _connectionThread;
};

#endif //_SESSION_H