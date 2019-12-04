#ifndef _CONNECTION_H
#define _CONNECTION_H

//std
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

//blowfish context
#include "crypto/blowfish.hpp"

#include "packets/packet.hpp"
#include "types.hpp"
#include "logger.hpp"

//Represents a client connection
class Connection : public std::enable_shared_from_this<Connection>
{
	
public:
	enum class State
	{
		CONNECTED = 1,
		DISCONNECTED = 2
	};
	using Ptr = std::shared_ptr<Connection>;
	using PacketHandler = std::function<void(ClientPacket&)>;
	using CloseHandler = std::function<void()>;

	Connection(TcpSocket&& socket);
	void SetHandlers(PacketHandler readHandler, CloseHandler closeHandler);
	void Read();
	void Write(std::vector<char>& buffer);
	void Close();
	BlowfishContext::Key GetAuthenticateKeyPart();
	void SendPacket(ServerPacket packet, BlowfishContext::CryptoType crypto = BlowfishContext::CryptoType::AUTHENTICATED);
	inline void SetEncryption(bool encrypted) { _encrypted = encrypted; };
	State state;
protected:
	void InitBlowfish(bool initial);
	void OnHeaderRead(const ErrorCode& ec);
	void OnPayloadRead(const ErrorCode& ec);
	void OnWrite(const ErrorCode& ec);
	TcpSocket _sock;
private:
	//useful for multithreading later
	using RecursiveLock = std::lock_guard<std::recursive_mutex>;
	std::recursive_mutex _lock;

	//Current packet being parsed
	ClientPacket _inPacket;

	//The client socket

	bool _encrypted;

	//Blowfish context
	BlowfishContext _blowfishCtx;

	//Called when the packet is ready 
	PacketHandler _packetHandler;

	//Called when the connection is closed
	CloseHandler _closeHandler;
};


#endif //_CONNECTION_H