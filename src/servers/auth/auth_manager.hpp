#ifndef AUTH_MANAGER_HPP
#define AUTH_MANAGER_HPP

#include <cstdint>
#include <memory>
#include <map>
#include <array>
#include <boost/uuid/uuid_generators.hpp>

#include "connection.hpp"
#include "handshake_event.hpp"

class AuthManager {

public:

	static AuthManager* Instance()
	{
		static AuthManager authManager;
		return &authManager;
	}

	uint32_t ValidateSession(boost::uuids::uuid uuid)
	{
		for (auto it = _tokens.begin(); it != _tokens.end(); it++)
		{
			if (uuid == it->second)
			{
				sLogger->Get()->info("Validated session for {0:d}", it->first);
				uint32_t uid{ it->first };
				_tokens.erase(it); 
				return uid;
			}
		}
		return uint32_t{ 0 };
	}

	uint8_t* AddLoginAttempt(uint32_t userId) {
		//Generate a random uuid on server side. So we can validate this user on the lobbyserver.
		sLogger->Get()->info("Adding login attempt for {0:d}", userId);
		boost::uuids::uuid uuid = _generator();
		_tokens[userId] = uuid;
		return uuid.data;
	};

	inline std::shared_ptr<Connection> GetLobby() { return _lobbyServer; };

	void SetLobbyServer(std::shared_ptr<Connection> lobbyServer)
	{
		_lobbyServer = lobbyServer;
	}

private:
	std::map<uint32_t, boost::uuids::uuid> _tokens;
	std::shared_ptr<Connection> _lobbyServer;
	boost::uuids::random_generator _generator;
};

#endif // !AUTH_MANAGER_HPP
