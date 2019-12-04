#include "server.hpp"

//std
#include <iostream>

#include <memory>

const std::string Server::ALL_INTERFACES = "0.0.0.0";

Server::Server()
	: _stopped { true }
	, _acceptSocket{ _ioService }

{
}

void Server::Initialize(const std::string& ipAddress, const uint16_t port, Server::AcceptHandler acceptHandler)
{
	sLogger->Get()->info("Initializing server...");
	boost::asio::ip::tcp::endpoint endpoint = { boost::asio::ip::address::from_string(ipAddress), port };
	try
	{
		_acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(_ioService, endpoint);
	}
	catch (const boost::system::error_code& ec)
	{
		sLogger->Get()->error("Failed to create acceptor {0}", ec.message());
	}

	_acceptHandler = acceptHandler;
}


bool Server::Accept()
{
	if (!_acceptor)
	{
		//Use std::cout for now
		sLogger->Get()->critical("The specified port is invalid");
		return false;
	}
	if (!_acceptHandler)
	{
		//Use std::cout for now
		sLogger->Get()->critical("There is no accept handler");
		return false;
	}
	_acceptSocket = TcpSocket{ _ioService };
	_acceptor->async_accept(_acceptSocket, [this](const ErrorCode& ec)
	{

		if (ec)
		{
			sLogger->Get()->critical("An error occured {0}", ec.message());
			return false;
		}
		else
		{
			try
			{
				_acceptSocket.non_blocking(true);
				_acceptHandler(std::move(_acceptSocket));
			}
			catch (const ErrorCode& error)
			{
				sLogger->Get()->critical("Accept callback exception", error.message());
			}

			if (!_stopped)
			{
				Accept();
			}
		}
		return true;
	});

	return true;
}

void Server::Run()
{
	_stopped = false;
	sLogger->Get()->info("Running server");
	_ioService.run();
}

bool Server::Stop()
{
	ErrorCode ec;
	_acceptor->close(ec);
	if (ec)
	{
		sLogger->Get()->critical("Acceptor::close failed {0}", ec.message());
		return false;
	}
	_stopped = true;
	if (_ioService.stopped()) 
	{
		//Server is already stopped
		return false;
	}

	_ioService.stop();
	return true;
}