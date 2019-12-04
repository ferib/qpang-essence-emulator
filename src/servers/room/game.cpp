#include "game.hpp"
#include "game_net_interface.hpp"

//std
#include <iostream>
#include "game_room.hpp"
#include <boost/thread.hpp>
#include "update_gameroom_event.hpp"
#include "game_connection.hpp"

template<typename ToClass, typename FromClass>
static ToClass& To(const FromClass& from)
{
	return dynamic_cast<ToClass&>(*from);
}

Game::Game()
	: _running{ false }
{
}

Game::~Game() = default;

void Game::Tick(uint64_t tick)
{
	Tickable::Tick(tick);

	std::lock_guard<std::mutex> lg{ _roomMx };

	for (auto room : _gameRooms)
	{
		room->Tick(tick);
	}
}

void Game::Loop()
{
	uint64_t tick{ 0 };

	while (true)
	{
		Tick(++tick);

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Game::PostEvent(GameNetEvent::Ptr netEvent)
{
	_eventThreadPool->Post(netEvent);
}

bool Game::InitializeThreadPool(const size_t threadCount)
{
	_eventThreadPool = std::make_unique<NetEventThreadPool>(threadCount,
		boost::bind(&Game::HandleEvent, this, boost::placeholders::_1));
	_eventThreadPool->Start();

	//for now..
	return true;
}

void Game::RunServer()
{
	_roomPacketHandler = new RoomPacketHandler();
	InitializeSettings();

	for (auto connector : _connectors)
	{
		connector->Connect();
	}

	TNL::Address a(TransportProtocol::IPProtocol, TNL::Address::NamedAddress::Any, 8020);
	try
	{
		_serverInterface = std::make_unique<GameNetInterface>(a);
		_serverInterface->setAllowsConnections(true);
	}
	catch (const std::exception & e)
	{
		std::cout << "Game::RunServer: exception: " << e.what() << std::endl;
		return;
	}
	_running = true;

	InitializeEventLoop();

	while (_running) {
		try
		{
			_serverInterface->processConnections();
			_serverInterface->checkIncomingPackets();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		catch (const std::exception& e)
		{
			sLogger->Get()->error(e.what());
		}
	}
	return;
}

void Game::InitializeSettings()
{
	_donPerKill = boost::lexical_cast<uint32_t>(sSettings->GetSetting("don_kill"));
	_donPerDeath = boost::lexical_cast<uint32_t>(sSettings->GetSetting("don_death"));
	_expPerKill = boost::lexical_cast<uint32_t>(sSettings->GetSetting("exp_kill"));
	_expPerDeath = boost::lexical_cast<uint32_t>(sSettings->GetSetting("exp_death"));
	_expPerSecond = boost::lexical_cast<uint32_t>(sSettings->GetSetting("exp_second"));
	_donRate = boost::lexical_cast<uint16_t>(sSettings->GetSetting("don_rate"));
	_expRate = boost::lexical_cast<uint16_t>(sSettings->GetSetting("exp_rate"));
}

void Game::HandleEvent(GameNetEvent::Ptr netEvent)
{

}

void Game::InitializeEventLoop()
{
	boost::thread t{ &Game::Loop, sGame };
}

Player::Ptr Game::FindPlayer(const GameConnection* connection)
{
	std::lock_guard<std::mutex> lg{ _playerMx };

	for (auto p : _players)
		if (p->GetConnection() == connection)
			return p;

	return nullptr;
}

Player::Ptr Game::FindPlayer(EventConnection * connection, uint32_t playerId)
{
	std::lock_guard<std::mutex> lg{ _playerMx };

	GameConnection* gameConnection = reinterpret_cast<GameConnection*>(connection);

	for (auto p : _players)
	{
		if (p->GetConnection() == gameConnection)
		{
			if (playerId == NULL)
			{
				return p;
			}
			else
			{
				if (p->GetIdentifier() == playerId)
				{
					return p;
				}
			}
		}
	}

	return nullptr;
}

Player::Ptr Game::FindPlayer(const uint32_t & playerId)
{
	std::lock_guard<std::mutex> lg{ _playerMx };

	for (auto player : _players)
	{
		if (player->GetIdentifier() == playerId)
		{
			return player;
		}
	}

	return nullptr;
}

void Game::RemovePlayerFromRoom(const GameRoom::Ptr & room, const Player::Ptr & player)
{
	if (room == nullptr || player == nullptr)
	{
		return;
	}

	room->RemovePlayer(player);
	player->UnsetRoom();

	if (room->GetPlayerCount() > 0)
	{
		OnUpdate(room);
	}
	else
	{
		RemoveRoom(room);
	}
}

Player::Ptr Game::CreatePlayer(GameConnection * connection, const uint32_t uid)
{
	std::lock_guard<std::mutex> lg{ _playerMx };
	auto player = std::make_shared<Player>(connection, uid);
	_players.push_back(player);
	return player;
}

void Game::HandleConnectorConnection(TcpSocket && sock)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(sock));
	auto session = std::make_shared<GameLobbySession>(conn);
	session->handler = _roomPacketHandler;
	_internalSessions.push_back(session);
	session->StartNetworking();
}

WeaponManager Game::Weapons()
{
	return _weaponManager;
}

LevelManager Game::Levels()
{
	return _levelManager;
}

SkillManager Game::Skills()
{
	return _skillManager;
}

GameRoom::Ptr Game::CreateRoom(const std::wstring & name, const uint8_t & map, const uint8_t & mode)
{
	std::lock_guard<std::mutex> lg(_roomMx);

	uint32_t maxId{ 1 };

	for (auto room : _gameRooms)
	{
		const auto roomIdentifier = room->GetIdentifier();

		if (roomIdentifier >= maxId)
		{
			maxId = roomIdentifier + 1;
		}
	}


	auto gameMode = _gameModeManager.GetMode(mode);

	//"room" placeholder because crash
	auto room = std::make_shared<GameRoom>(maxId, "room", gameMode, map);
	_gameRooms.push_back(room);

	return room;
}

void Game::OnLobbyServerConnected(Connector & lobbyConnector)
{
	auto conn = std::make_shared<Connection>(std::forward<TcpSocket>(*lobbyConnector.getSocket()));
	conn->SendPacket(IAmRoomEvent{}.Compose(conn), BlowfishContext::CryptoType::PUBLIC);
	conn->SetEncryption(false);
	_lobbyServer = conn;
}

GameRoom::Ptr Game::GetRoom(const uint32_t & roomId)
{
	std::lock_guard<std::mutex> lg(_roomMx);

	for (auto room : _gameRooms)
		if (room->GetIdentifier() == roomId)
			return room;

	return nullptr;
}

GameMode * Game::FindGameMode(const uint8_t & mode)
{
	return _gameModeManager.GetMode(mode);
}

void Game::RemoveRoom(const GameRoom::Ptr & targetRoom)
{
	std::lock_guard<std::mutex> lg(_roomMx);

	targetRoom->Close();

	_gameRooms.erase(std::find(
		_gameRooms.begin(),
		_gameRooms.end(),
		targetRoom
	));
}

//TODO: Remove room.. Fix crashes by removing room..
void Game::RemovePlayer(const Player::Ptr & targetPlayer)
{
	auto room = targetPlayer->GetRoom();

	if (room != nullptr)
	{
		RemovePlayerFromRoom(room, targetPlayer);
	}

	std::lock_guard<std::mutex> lg(_playerMx);

	_players.erase(std::find(
		_players.begin(),
		_players.end(),
		targetPlayer));
}

void Game::Announce(const std::string & announcement)
{
	// TODO: Implement
}

void Game::Whisper(const Player::Ptr & player, const std::string & message)
{
	// TODO: Implement
}

void Game::OnUpdate(GameRoom::Ptr room)
{
	Lobby()->SendPacket(UpdateGameRoomEvent{ room }.Compose(nullptr));
}
