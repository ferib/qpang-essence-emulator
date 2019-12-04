#ifndef _SERVER_HPP
#define _SERVER_HPP

//std
#include <atomic>
#include <cstdint>
#include <boost/format.hpp>

//boost::asio
#include "types.hpp"
#include "logger.hpp"
#include "connector.hpp"

class Server
{
public:
	static const std::string ALL_INTERFACES;

	using AcceptHandler = std::function<void(TcpSocket&&)>;
	using ConnectorCallback = AcceptHandler;

	Server();
	void Initialize(const std::string& ipAddress, const uint16_t port, AcceptHandler acceptHandler);
	bool Accept();
	void Run();
	
	bool Stop();

protected:
	inline boost::asio::io_service& GetIo() { return _ioService; }

private:
	//_ioService needs to be declared before _acceptor
	boost::asio::io_service _ioService;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> _acceptor;
	boost::asio::ip::tcp::socket _acceptSocket;
	boost::asio::ip::tcp::endpoint _endpoint;
	AcceptHandler _acceptHandler;
	ConnectorCallback _connectorCallback;
	bool _stopped;
	Logger* _logger;
};

#endif //_SERVER_HPP