#include "game_room.hpp"

#include <utility>
#include "game.hpp"
#include "game_connection.hpp"

GameRoom::GameRoom(uint32_t identifier, std::string name, GameMode* mode, uint8_t map)
	: m_state(WAITING), m_mode(mode), m_identifier(identifier), m_name(std::move(name)), m_map(map)
{
}

GameRoom::~GameRoom()
{
}

void GameRoom::Tick(uint64_t tick)
{
	Tickable::Tick(tick);

	if (m_session != nullptr)
	{
		m_session->Tick(tick);
	}
}

void GameRoom::AddPlayer(Player::Ptr player)
{
	InsertPlayer(player);
	BalancePlayer(player);
	player->SetRoom(shared_from_this());
	Sync();
}

void GameRoom::RemovePlayer(Player::Ptr player)
{

	if (player == nullptr)
	{
		return;
	}

	KickPlayer(player->GetIdentifier());

	if (player->GetIdentifier() == m_masterIdentifier)
	{
		FindNewMaster();
	}

	if (m_session != nullptr && player->GetSession() != nullptr)
	{
		m_session->RemovePlayer(player);
	}

	std::lock_guard<std::mutex> lg(m_playerMx);

	m_players.erase(std::find(
		m_players.begin(),
		m_players.end(),
		player
	));

	Sync();
}

void GameRoom::KickPlayer(uint32_t playerIdentifier, uint32_t cmd)
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	std::for_each(m_players.begin(), m_players.end(), [masterId = uint32_t(m_masterIdentifier), playerIdentifier, cmd](Player::Ptr & player)
	{
		player->GetConnection()->KickPlayer(playerIdentifier, masterId, cmd);
	});
}

Player::Ptr GameRoom::GetPlayer(const GameConnection* gameConnection)
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	const auto player = std::find_if(m_players.begin(), m_players.end(),
		[gameConnection](const Player::Ptr & player)
		{
			return player->GetConnection() == gameConnection;
		});

	return *player;
}

Player::Ptr GameRoom::GetPlayer(uint32_t identifier)
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	const auto player = std::find_if(m_players.begin(), m_players.end(),
		[identifier](Player::Ptr & player)
		{
			return player->GetIdentifier() == identifier;
		});

	return *player;
}

void GameRoom::OnPlayerLoaded(Player::Ptr player)
{
	player->SetState(PlayerState::WAITING_FOR_PLAYERS);

	if (m_session != nullptr)
	{
		m_session->OnPlayerLoaded(player);
	}
}

void GameRoom::OnPlayerLeft(Player::Ptr player)
{
	auto session = player->GetSession();

	if (m_session != nullptr)
	{
		m_session->RemovePlayer(player);
	}

	if (session != nullptr)
	{
		player->ApplySession();
	}
}

void GameRoom::Start()
{
	if (m_state != RoomState::WAITING)
		return;

	srand(time(NULL));

	m_state = RoomState::PLAYING;

	m_session = std::make_shared<GameRoomSession>(m_mode, m_map, m_isPointsGame ? m_points : m_time, m_isPointsGame);

	m_session->Intitialize();

	std::lock_guard<std::mutex> lg(m_playerMx);

	for (auto player : m_players)
	{
		if (player->GetState() == PlayerState::READY)
		{
			m_session->AddPlayer(player);
			player->SetState(PlayerState::LOADING);
			player->GetConnection()->EnterGame(player);
		}
		else 
		{
			// This is needed to show that the room went into a game..
			player->GetConnection()->SetGameState(3, player->GetIdentifier());
			player->GetConnection()->OnPlayerChange(player, NULL, NULL);
		}
	}

	Sync();
}

void GameRoom::Stop()
{
	m_state = RoomState::ENDING;
}

void GameRoom::End()
{
	m_session.reset();
}

void GameRoom::Close()
{
	m_players.clear();
}

void GameRoom::BalancePlayers()
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	Team team = Team::NONE;

	for (auto playerToBalance : m_players)
	{
		if (!m_mode->IsTeamMode())
		{
			playerToBalance->SetTeam(Team::NONE);

			continue;
		}

		playerToBalance->SetTeam(team);

		for (auto player : m_players)
		{
			player->GetConnection()->SetPlayerTeam(playerToBalance, team);
		}

		team = team == Team::BLUE ? Team::YELLOW : Team::BLUE;
	}
}

void GameRoom::BalancePlayer(Player::Ptr player)
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	auto team = Team::NONE;

	player->SetTeam(team);

	if (m_mode->IsTeamMode())
	{
		size_t blueAmount = std::count_if(m_players.begin(), m_players.end(),
			[](const Player::Ptr & player) { return player->GetTeam() == Team::BLUE; });

		team = blueAmount * 2 >= m_players.size() ? Team::YELLOW : Team::BLUE;
	}

	player->SetTeam(team);
}

void GameRoom::SetMap(uint8_t map)
{
	m_map = map;

	Sync();
}

void GameRoom::SetMode(GameMode* gameMode)
{
	m_mode = gameMode;

	m_mode->OnApply(shared_from_this());

	Sync();
}

void GameRoom::SetPassword(std::string password)
{
	m_password = password;

	Sync();
}

void GameRoom::SetNewMaster(uint32_t playerIdentifier)
{
	m_masterIdentifier = playerIdentifier;

	Sync();
}

void GameRoom::SetMaxPlayerCount(uint32_t maxPlayerCount)
{
	m_maxPlayerCount = maxPlayerCount;

	Sync();
}

void GameRoom::SetSkillsEnabled(uint8_t enabled)
{
	m_skillsEnabled = enabled;

	Sync();
}

void GameRoom::SetPointsGame(uint8_t isPoints)
{
	m_isPointsGame = isPoints;
}

void GameRoom::SetPointsGoal(uint8_t points)
{
	m_points = points;

	Sync();
}

void GameRoom::SetTimeGoal(uint8_t minutes)
{
	m_time = minutes;

	Sync();
}

void GameRoom::AddPlayerToRoom(Player::Ptr newPlayer)
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	for (auto player : m_players)
	{
		if (newPlayer->GetIdentifier() != player->GetIdentifier())
		{
			player->GetConnection()->AddPlayerToRoom(newPlayer);
		}

		newPlayer->GetConnection()->AddPlayerToRoom(player);
	}
}

void GameRoom::RemovePlayerFromRoom(Player::Ptr playerToRemove)
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	for (auto player : m_players)
	{
		if (playerToRemove->GetIdentifier() != player->GetIdentifier())
		{
			player->GetConnection()->KickPlayer(playerToRemove->GetIdentifier(), m_masterIdentifier, 0);
		}
	}
}

uint32_t GameRoom::FindNewMaster()
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	for (auto player : m_players)
	{
		const auto playerIdentifier = player->GetIdentifier();

		if (playerIdentifier != m_masterIdentifier)
		{
			SetNewMaster(playerIdentifier);
			return playerIdentifier;
		}
	}

	return NULL;
}

RoomState GameRoom::GetState() const
{
	return m_state;
}

std::string GameRoom::GetName() const
{
	return m_name;
}

uint32_t GameRoom::GetIdentifier() const
{
	return m_identifier;
}

GameMode* GameRoom::GetMode() const
{
	return m_mode;
}

uint8_t GameRoom::GetPlayerCount()
{
	return m_players.size();
}

uint32_t GameRoom::GetMasterIdentifier() const
{
	return m_masterIdentifier;
}

uint8_t GameRoom::GetMaxPlayerCount() const
{
	return m_maxPlayerCount;
}

uint8_t GameRoom::GetMap() const
{
	return m_map;
}

std::string GameRoom::GetPassword() const
{
	return m_password;
}

bool GameRoom::IsPointsGame() const
{
	return m_isPointsGame;
}

uint32_t GameRoom::GetTimeGoal() const
{
	return m_time;
}

uint32_t GameRoom::GetPointGoal() const
{
	return m_points;
}

GameRoomSession::Ptr GameRoom::GetSession() const
{
	return m_session;
}

bool GameRoom::IsPlaying() const
{
	return m_state == RoomState::PLAYING || m_state == RoomState::PLAYING_UNK || m_state == RoomState::ENDING;
}

bool GameRoom::IsMeleeOnly() const
{
	return m_meleeOnly;
}

bool GameRoom::HasPassword() const
{
	return !m_password.empty();
}

bool GameRoom::HasSkillsEnabled() const
{
	return m_skillsEnabled;
}

void GameRoom::InsertPlayer(Player::Ptr player)
{
	std::lock_guard<std::mutex> lg(m_playerMx);

	m_players.push_back(player);
}

void GameRoom::Sync()
{
	sGame->OnUpdate(shared_from_this());
}
