//std
#include <iostream>
#include <memory>

//this
#include "connection.hpp"

//bind
#include "boost/bind.hpp"


Connection::Connection(TcpSocket&& sock)
	: _sock{ std::move(sock) }
	, state {State::CONNECTED}
	, _encrypted{ true }
	, _inPacket{}
	, _blowfishCtx{}
{
}

void Connection::SetHandlers(PacketHandler packetHandler, CloseHandler closeHandler)
{
	_packetHandler = packetHandler;
	_closeHandler = closeHandler;
	
}

void Connection::SendPacket(ServerPacket packet, BlowfishContext::CryptoType crypto)
{
	if (this == nullptr)
		return;


	packet.AppendChecksum();

	std::vector<char> sendBuf;
	//Allocate enough space to store the packet
	sendBuf.resize(sizeof(PacketHeader) + packet.buffer.size());
	packet.header.fullLength = static_cast<uint16_t>(sendBuf.size());
	//Copy the header
	if (_encrypted)
	{
		packet.header.encrypted = true;
	}
	memcpy(sendBuf.data(), &packet.header, 4);

	//Copy the payload header
	auto payloadHdr = packet.ReadPayloadHeader();
	memcpy(sendBuf.data() + 4, &payloadHdr, 4);

	//Copy the data
	if (packet.buffer.size() > 4)
	{
		std::copy(packet.buffer.cbegin() + 4, packet.buffer.cend(), sendBuf.begin() + 8);
	}



	//Encrypt if needed
	if (_encrypted)
	{
		//TODO: SEE THIS:
		//http://coliru.stacked-crooked.com/a/621b67959a1d4880
		_blowfishCtx.Initialize(crypto);
		std::vector<char> buf{ sendBuf.cbegin() + 4, sendBuf.cend() };
		_blowfishCtx.Encrypt(buf, crypto);
		if (sendBuf.size() != buf.size())
		{
			sendBuf.resize(4 + buf.size());
		}
		std::copy(buf.cbegin(), buf.cend(), sendBuf.begin() + 4);
	}

	Write(sendBuf);

}

BlowfishContext::Key Connection::GetAuthenticateKeyPart()
{
	_blowfishCtx.Initialize(BlowfishContext::CryptoType::AUTHENTICATED);
	return _blowfishCtx.GetKeyPart();
}

void Connection::Read()
{
	RecursiveLock rl{ _lock };
	if (state == State::DISCONNECTED)
	{
		return;
	}

	try
	{
		//Read the first four bytes (unencrypted)
		boost::asio::async_read(
			_sock, 
			boost::asio::buffer(&_inPacket.header, 4), 
			boost::bind(
				&Connection::OnHeaderRead, 
				shared_from_this(), 
				boost::asio::placeholders::error));
	}
	catch (const ErrorCode& ec)
	{
		std::cout << "Connection::Read: async_read failed: " << ec.message() << "\n";
		Close();
	}
}

void Connection::Write(std::vector<char>& buffer)
{
	try
	{
		boost::asio::async_write(
			_sock,
			boost::asio::buffer(buffer.data(), buffer.size()),
			boost::bind(&Connection::OnWrite,
				shared_from_this(),
				boost::asio::placeholders::error));
	}
	catch (const ErrorCode& ec)
	{
		std::cout << "Connection::Write: async_write failed: " << ec.message() << "\n";
		Close();
	}
}

void Connection::OnWrite(const ErrorCode& ec)
{
	if (ec)
	{
		std::cout << "Connection::OnWrite: exception: " << ec.message() << "\n";
		Close();
	}
}

void Connection::Close()
{
	RecursiveLock rl{ _lock };

	if (state != State::DISCONNECTED)
	{
		_sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		_sock.close();
		state = State::DISCONNECTED;
		_closeHandler();
	}
}


void Connection::OnHeaderRead(const ErrorCode& ec)
{
	RecursiveLock rl{ _lock };

	if (ec)
	{
		Close();
		return;
	}
	auto length = _inPacket.header.fullLength;
	if (length < sizeof(PacketHeader))
	{
		std::cout << "Connection::OnHeaderRead: invalid length: " << length << "\n";
		Close();
		return;
	}

	_inPacket.buffer.resize(_inPacket.header.fullLength - 4);

	try
	{
		//Read the remaining bytes
		boost::asio::async_read(
			_sock,
			boost::asio::buffer(_inPacket.buffer, _inPacket.buffer.size()),
			boost::bind(
				&Connection::OnPayloadRead,
				shared_from_this(),
				boost::asio::placeholders::error));
	}
	catch (const ErrorCode& ec)
	{
		std::cout << "Connection::Read: async_read failed: " << ec.message() << "\n";
		Close();
	}
}

void Connection::OnPayloadRead(const ErrorCode& ec)
{
	RecursiveLock rl{ _lock };

	if (ec)
	{
		std::cout << "Connection::OnPayloadRead: exception: " << ec.message() << "\n";
		Close();
		return;
	}

	if (_encrypted)
	{
		auto crypto = _blowfishCtx.publicBfInitialized
			? BlowfishContext::CryptoType::AUTHENTICATED
			: BlowfishContext::CryptoType::PUBLIC;

		_blowfishCtx.Initialize(crypto);
		_blowfishCtx.Decrypt(_inPacket.buffer, crypto);
	}

	if(state == State::CONNECTED) _packetHandler(_inPacket);

	//Initiate another asynchronous read
	Read();
}