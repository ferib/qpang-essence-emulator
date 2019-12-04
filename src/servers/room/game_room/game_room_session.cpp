#include "game_room_session.hpp"
#include "game_connection.hpp"

#include "cg_game_state.hpp"
#include "gc_respawn.hpp"
#include "gc_join.hpp"

#include "gc_move.hpp"
#include "gc_motion.hpp"
#include "gc_shoot.hpp"
#include "gc_card.hpp"
#include "gc_weapon.hpp"
#include "gc_hit.hpp"

#include <memory>
#include <algorithm>

GameRoomSession::GameRoomSession(GameMode* mode, uint8_t map, uint32_t goal, bool isPoints) :
	m_mode(mode),
	m_map(map),
	m_goal(goal),
	m_isPoints(isPoints),
	m_state(State::WAITING)
{
}

void GameRoomSession::Intitialize()
{
	m_playerSpawner = std::make_unique<PlayerSpawner>();
	m_itemManager = std::make_unique<GameItemManager>();

	m_playerSpawner->Load(m_mode->GetModeIdentifier(), m_map);
	m_itemManager->Load(m_map);
}

void GameRoomSession::Tick(uint64_t tick)
{
	Tickable::Tick(tick);
}

void GameRoomSession::AddPlayer(Player::Ptr player)
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	player->RefreshSession();

	m_players.push_back(player);
}

void GameRoomSession::RemovePlayer(Player::Ptr player)
{
	m_mode->OnPlayerLeave(shared_from_this(), player);

	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	std::vector<Player::Ptr>::iterator it = std::remove(m_players.begin(), m_players.end(), player);

	m_players.erase(it, m_players.end());
}

void GameRoomSession::OnPlayerLoaded(Player::Ptr player)
{
	if (m_state == State::FINISHING || m_state == State::ENDED)
	{
		return;
	}

	m_mode->OnPlayerLoaded(shared_from_this(), player);

	if (m_state == State::PLAYING)
	{
		m_mode->OnPlayerMidGameJoin(shared_from_this(), player);
	}

	if (m_state == State::WAITING)
	{
		if (CanStart())
		{
			Start();
		}
	}
}

void GameRoomSession::RelayMove(CGMove move)
{
	Relay<GCMove>(move);
}

void GameRoomSession::RelayShoot(CGShoot shoot)
{
	Relay<GCShoot>(shoot);
}

void GameRoomSession::RelayMotion(CGMotion motion)
{
	Relay<GCMotion>(motion);
}

void GameRoomSession::RelayAbility(CGCard card)
{
	Relay<GCCard>(card);
}

void GameRoomSession::RelayWeapon(CGWeapon weapon)
{
	Relay<GCWeapon>(weapon);
}

void GameRoomSession::RelayHit(CGHit hit, uint16_t damage, uint16_t newHealth, uint16_t streak)
{
	Relay<GCHit>(hit, newHealth, damage, 0, streak);
}

void GameRoomSession::KillPlayer(Player::Ptr killer, Player::Ptr target, uint32_t itemIdentifier, bool isHeadshot)
{
	m_mode->OnPlayerKill(shared_from_this(), killer, target);

	AddKillfeed(killer->GetIdentifier(), target->GetIdentifier(), itemIdentifier, isHeadshot);
}


void GameRoomSession::Start()
{
	m_state = PLAYING;

	ShowStart();

	InitPlayers();

	m_mode->OnStart(shared_from_this());
}

void GameRoomSession::Stop()
{
	m_state = FINISHING;
}

void GameRoomSession::End()
{
	m_state = ENDED;

	m_mode->OnSave(shared_from_this());

	m_playerSpawner.reset();
}

void GameRoomSession::Clear()
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	m_players.clear();
}

void GameRoomSession::Load()
{
	m_playerSpawner = std::make_unique<PlayerSpawner>();

	m_playerSpawner->Load(m_mode->GetModeIdentifier(), m_map);
}

GameRoomSession::State GameRoomSession::GetState()
{
	return m_state;
}

bool GameRoomSession::CanStart()
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	size_t waitingCount = std::count_if(m_players.begin(), m_players.end(),
		[](Player::Ptr player) { return player->GetState() == PlayerState::WAITING_FOR_PLAYERS; });

	return waitingCount == m_players.size();
}

void GameRoomSession::ShowStart()
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	std::for_each(m_players.begin(), m_players.end(),
		[](Player::Ptr player) { player->GetConnection()->SetGameState(CGGameState::SEND_GAME_STATE_PLAY); });
}

void GameRoomSession::InitPlayers()
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	std::for_each(m_players.begin(), m_players.end(),
		[this](Player::Ptr player) { InitPlayer(player); });
}

void GameRoomSession::InitPlayer(Player::Ptr loadedPlayer)
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	for (Player::Ptr player : m_players)
	{
		if (player != loadedPlayer)
		{
			if (loadedPlayer->GetSession()->HasConnection(player->GetIdentifier()))
			{
				//this will never occur.. but just for programming's sake.
				continue;
			}

			LoadForBoth(player, loadedPlayer);
		}
	}
}

void GameRoomSession::SpawnPlayers()
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	std::for_each(m_players.begin(), m_players.end(),
		[this](Player::Ptr player) { SpawnPlayer(player); });
}

void GameRoomSession::SpawnPlayer(Player::Ptr playerToSpawn)
{
	if (!playerToSpawn->IsPlaying())
		return;

	Spawn spawn = m_playerSpawner->GetRandomSpawnForTeam(playerToSpawn->GetTeam());

	m_mode->OnPlayerSpawn(shared_from_this(), playerToSpawn, spawn);

	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	std::for_each(m_players.begin(), m_players.end(),
		[playerToSpawn, spawn](Player::Ptr player)
		{
			player->GetConnection()->SpawnPlayer(playerToSpawn, spawn);
		});

	RegisterEvent(std::bind(&GameRoomSession::RemoveInvincibility, this, playerToSpawn->GetIdentifier()), GetTick() + 5);
}

void GameRoomSession::SpawnPlayersFor(Player::Ptr player)
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	std::for_each(m_players.begin(), m_players.end(),
		[player](Player::Ptr playerToSpawn)
		{
			if (player == playerToSpawn)
			{
				return;
			}
			player->GetConnection()->SpawnPlayer(playerToSpawn, { 0xFF, 0xFF, 0xFF });
			player->GetConnection()->RemoveInvincibility(playerToSpawn->GetIdentifier());
		});
}

void GameRoomSession::StartRespawning(Player::Ptr player, uint8_t seconds)
{
	RegisterEvent(std::bind(&GameRoomSession::SpawnPlayer, this, player), GetTick() + seconds);
}

void GameRoomSession::RemoveInvincibility(uint32_t targetId)
{
	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	std::for_each(m_players.begin(), m_players.end(),
		[targetId](Player::Ptr player)
		{
			if (player == nullptr)
				return;

			if (player->GetIdentifier() == targetId)
			{
				player->GetSession()->SetInvincible(false);
			}

			player->GetConnection()->RemoveInvincibility(targetId);
		});
}

void GameRoomSession::AddKillfeed(uint32_t killerIdentifier, uint32_t targetIdentifier, uint32_t weaponIdentifier, bool isHeadshot)
{
	Relay<GCGameState>(
		targetIdentifier,
		isHeadshot ? CGGameState::KILLFEED_ADD_HEAD : CGGameState::KILLFEED_ADD,
		weaponIdentifier,
		killerIdentifier
		);
}

ScoreBoard GameRoomSession::GenerateScoreBoard()
{
	auto scoreBoard = ScoreBoard();

	std::lock_guard<std::recursive_mutex> lg(m_playerMx);

	for (auto player : m_players)
	{
		scoreBoard.AddPlayer(ScoreBoard::Player{
			player->GetIdentifier(),
			player->GetLevel(),
			player->GetTeam(),
			player->GetName(),
			player->GetSession()->GetKills(),
			player->GetSession()->GetDeaths(),
			0
			});
	}

	return scoreBoard;
}

void GameRoomSession::LoadForBoth(Player::Ptr player1, Player::Ptr player2)
{
	AddPlayerTo(player2, player1);
	ConnectPlayerTo(player2, player1);

	AddPlayerTo(player1, player2);
	ConnectPlayerTo(player1, player2);

	player1->GetSession()->AddConnection(player2->GetIdentifier());
	player2->GetSession()->AddConnection(player1->GetIdentifier());
}

void GameRoomSession::AddPlayerTo(Player::Ptr player, Player::Ptr playerToAdd)
{
	player->GetConnection()->AddPlayerToRoom(playerToAdd);
}

void GameRoomSession::ConnectPlayerTo(Player::Ptr player, Player::Ptr playerToConnect)
{
	player->GetConnection()->ConnectPlayer(player->GetIdentifier(), playerToConnect->GetIdentifier());
}