#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include <string>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/asio/basic_socket.hpp>
#include <boost/format.hpp>
#include <boost/bind.hpp>
#include "logger.hpp"

using boost::asio::ip::tcp;

class Server;

//TODO derive from class Connection. right now mutex makes it crash.
class Connector {
	using IOService = boost::asio::io_service;
	using ConnectCallback = std::function<void(Connector&)>;

public:
	Connector(std::string address, uint32_t port, ConnectCallback connectCallback);
	~Connector();
	void Connect();
	inline tcp::socket* getSocket() { return _socket; }
	inline bool isConnected() { return _connected; };
private:
	void OnConnect(const boost::system::error_code&);
	tcp::resolver::iterator _endpointIterator;
	IOService _io;
	tcp::socket* _socket;
	Logger* _logger;
	ConnectCallback _connectCallback;
	bool _connected;
};

#endif