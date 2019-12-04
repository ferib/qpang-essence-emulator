#ifndef _GAME_HPP
#define _GAME_HPP

#include "game_net_event.hpp"
#include "game_room.hpp"
#include "player.hpp"
#include <threading/thread_pool.hpp>
#include "connector.hpp"
#include "settings_manager.hpp"
#include "i_am_room_event.hpp"
#include "logger.hpp"
#include "room_packet_handler.hpp"
#include "game_lobby_session.hpp"
#include "weapon_manager.hpp"
#include "skill_manager.hpp"
#include "tickable.hpp"

#include "game_mode.hpp"

//std
#include <array>
#include <map>
#include <mutex>
#include "level_manager.hpp"
#include "game_mode_manager.hpp"

class GameNetInterface;

class Game : public Tickable
{
	using NetEventThreadPool = EventThreadPool<GameNetEvent>;

public:
	Game();
	~Game();


	void Tick(uint64_t tick) override;
	void Loop();

	static Game* Instance()
	{
		static Game game;
		return &game;
	}

	bool InitializeThreadPool(const size_t threadCount);
	void RunServer();
	void InitializeSettings();

	void PostEvent(GameNetEvent::Ptr netEvent);
	void HandleConnectorConnection(TcpSocket&& sock);

	WeaponManager Weapons();
	LevelManager Levels();
	SkillManager Skills();

	GameRoom::Ptr CreateRoom(const std::wstring& name, const uint8_t& map, const uint8_t& mode);
	GameRoom::Ptr GetRoom(const uint32_t& id);

	GameMode* FindGameMode(const uint8_t& mode);

	void RemoveRoom(const GameRoom::Ptr& room);
	void RemovePlayer(const Player::Ptr& player);

	void Announce(const std::string& announcement);
	void Whisper(const Player::Ptr& player, const std::string& message);

	void OnUpdate(GameRoom::Ptr room);

	Player::Ptr CreatePlayer(GameConnection* connection, const uint32_t uid);
	Player::Ptr FindPlayer(const GameConnection* connection);
	Player::Ptr FindPlayer(EventConnection* connection, const uint32_t playerId = NULL);
	Player::Ptr FindPlayer(const uint32_t& playerId);

	void RemovePlayerFromRoom(const GameRoom::Ptr& room, const Player::Ptr& player);

	void OnLobbyServerConnected(Connector& lobbyConnector);
	inline Connection::Ptr Lobby() { return _lobbyServer; };

	inline uint32_t KillDonAmount() { return _donPerKill; };
	inline uint32_t DeathDonAmount() { return _donPerDeath; };
	inline uint32_t KillExpAmount() { return _expPerKill; };
	inline uint32_t DeathExpAmount() { return _expPerDeath; };
	inline uint32_t SecondExpAmount() { return _expPerSecond; };

	inline uint16_t DonRate() { return _donRate; };
	inline uint16_t ExpRate() { return _expRate; };

protected:
	void HandleEvent(GameNetEvent::Ptr);
private:

	void InitializeEventLoop();

	bool _running = false;
	std::mutex _playerMx;
	std::mutex _roomMx;
	Connection::Ptr _lobbyServer;
	std::unique_ptr<NetEventThreadPool> _eventThreadPool;
	std::unique_ptr<GameNetInterface> _serverInterface;
	std::vector<Player::Ptr> _players;
	std::vector<GameRoom::Ptr> _gameRooms;
	std::vector<GameLobbySession::Ptr> _internalSessions;

	std::array<Connector*, 1> _connectors = {
		new Connector(sSettings->GetSetting("lobby_host"), 8005, std::bind(&Game::OnLobbyServerConnected, this, std::placeholders::_1))
	};

	uint32_t _donPerKill{0};
	uint32_t _donPerDeath{0};
	uint32_t _expPerKill{0};
	uint32_t _expPerDeath{0};
	uint32_t _expPerSecond{0};

	uint16_t _expRate{0};
	uint16_t _donRate{0};

	WeaponManager _weaponManager{};
	SkillManager _skillManager{};
	LevelManager _levelManager{};
	GameModeManager _gameModeManager{};
	RoomPacketHandler* _roomPacketHandler;
	Logger* _logger;
};

#define sGame Game::Instance()

#endif //_GAME_HPP