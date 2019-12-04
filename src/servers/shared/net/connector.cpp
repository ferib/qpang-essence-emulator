#include "connector.hpp"
#include "server.hpp"
#include <iostream>


Connector::Connector(std::string address, uint32_t port, ConnectCallback connectCallback)
{
	_connected = false;
	_connectCallback = connectCallback;
	tcp::resolver resolver(_io);
	tcp::resolver::query query(tcp::v4(), address, std::to_string(port));
	_endpointIterator = resolver.resolve(query);
	_socket = new tcp::socket(_io);
}

void Connector::Connect()
{
	sLogger->Get()->info("Attempting connection towards: {0}:{1:d} ");
	boost::asio::async_connect(_socket->lowest_layer(), _endpointIterator, 
		std::bind(&Connector::OnConnect, this, std::placeholders::_1));
	_io.run();
}

void Connector::OnConnect(const boost::system::error_code& code)
{

	if (!code)
	{
		_socket->non_blocking(true);
		sLogger->Get()->info("Connected");
		_connected = true;
		_connectCallback(*this);
	}
	else
	{
		sLogger->Get()->critical("Failed to connect");
	}
}

Connector::~Connector()
{

}