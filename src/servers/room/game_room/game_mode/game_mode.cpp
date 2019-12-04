#include "game_mode.hpp"
#include <utility>
#include "game_room.hpp"
#include "game.hpp"
#include "game_room_session.hpp"
#include "mode.hpp"
#include "game_connection.hpp"

GameMode::GameMode()
{
}

GameMode::~GameMode()
{

}

void GameMode::OnApply(const std::shared_ptr<GameRoom>& room)
{
}

void GameMode::OnStart(const GameRoomSession::Ptr& roomSession)
{
	roomSession->SpawnPlayers();
}

void GameMode::OnPlayerMidGameJoin(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr & player)
{
	player->GetConnection()->SetGameState(4);

	roomSession->InitPlayer(player);
	roomSession->SpawnPlayer(player);
	roomSession->SpawnPlayersFor(player);
}

void GameMode::OnPlayerLoaded(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr & player)
{

}

void GameMode::OnPlayerStart(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player)
{

}

void GameMode::OnPlayerLeave(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player)
{
	sLogger->Get()->debug("GameMode OnPlayerLeave");

	player->SetState(PlayerState::IDLING);
}

void GameMode::OnPlayerKill(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& killer, const Player::Ptr& target)
{
	killer->GetSession()->AddKill();
	killer->GetSession()->AddStreak();

	target->GetSession()->AddDeath();
	target->GetSession()->ResetStreak();

	roomSession->StartRespawning(target, 10);
}

void GameMode::OnPlayerSpawn(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player, const Spawn& spawn)
{
	player->GetSession()->SetInvincible(true);
	player->GetSession()->ResetHealth();
	player->GetConnection()->RefillAllWeapons(player);
}

void GameMode::OnCheckScore(GameRoom* room)
{
	sLogger->Get()->debug("Gameroom {0:d} checking score");
}

void GameMode::OnSave(const std::shared_ptr<GameRoomSession>& room)
{
	
}

bool GameMode::IsTeamMode()
{
	return true;
}

std::string GameMode::GetName()
{
	return "unset";
}

uint8_t GameMode::GetModeIdentifier()
{
	return Mode::PRACTICE;
}
