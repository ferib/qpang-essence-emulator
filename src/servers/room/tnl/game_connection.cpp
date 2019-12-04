#include "game_connection.hpp"
#include "game.hpp"

#include <vector>
#include <array>

#include "gc_exit.hpp"
#include "gc_room.hpp"
#include "gc_pve_npc_init.hpp"
#include "gc_game_state.hpp"
#include "gc_join.hpp"
#include "gc_room_info.hpp"
#include "gc_player_change.hpp"
#include "cg_player_change.hpp"
#include "gc_mesg.hpp"
#include "gc_start.hpp"
#include "gc_arranged_accept.hpp"
#include "cg_game_state.hpp"
#include "gc_respawn.hpp"
#include "gc_hit.hpp"
#include "gc_weapon.hpp"
#include "gc_game_item.hpp"

#include "tnlNetInterface.h"

TNL_IMPLEMENT_NETCONNECTION(GameConnection, NetClassGroupGame, true);

GameConnection::GameConnection()
{
}

void GameConnection::onConnectionEstablished()
{
	setIsConnectionToClient();
	setPingTimeouts(1000, 3);
}

void GameConnection::onConnectionTerminated(TerminationReason reason, const char* errorDisconnectString)
{
	setConnectionState(NetConnectionState::Disconnected);

	auto player = sGame->FindPlayer(this);

	if (player != nullptr)
	{
		sGame->RemovePlayer(player);
	}
}


void GameConnection::onConnectTerminated(TerminationReason reason, const char* errorDisconnectString)
{
	setConnectionState(NetConnectionState::Disconnected);

	auto player = sGame->FindPlayer(this);

	if (player != nullptr)
	{
		sGame->RemovePlayer(player);
	}
}

void GameConnection::SetGameState(uint32_t cmd, uint32_t playerIdentifier,
	uint32_t value, uint32_t valueIdentifier)
{
	Send(new GCGameState(playerIdentifier, cmd, value, valueIdentifier));
}
 
void GameConnection::OnPlayerChange(Player::Ptr player, uint32_t cmd, uint32_t value)
{
	Send(new GCPlayerChange(player, cmd, value));
}

void GameConnection::CreateRoom(uint32_t playerId, uint8_t cmd, GameRoom::Ptr room)
{
	Send(new GCRoom(playerId, cmd, room));
}

void GameConnection::SetRoomInfo(GameRoom::Ptr room)
{
	Send(new GCRoomInfo(room));
}

void GameConnection::AddPlayerToRoom(Player::Ptr player)
{
	Send(new GCJoin(player));
}

void GameConnection::KickPlayer(uint32_t playerIdentifier, uint32_t masterIdentifier, uint32_t cmd)
{
	Send(new GCExit(playerIdentifier, cmd, masterIdentifier));
}

void GameConnection::SetPlayerTeam(Player::Ptr player, Team team)
{
	Send(new GCPlayerChange(player, CGPlayerChange::TEAM, team));
}

void GameConnection::SendPlayerMessage(uint32_t playerIdentifier, std::wstring nickname, std::wstring message)
{
	Send(new GCMesg(playerIdentifier, 1, nickname, message));
}

void GameConnection::EnterGame(Player::Ptr player)
{
	if (player->GetRoom() == nullptr)
	{
		return;
	}

	Send(new GCStart(player));
	Send(new GCJoin(player));
	Send(new GCGameState(player->GetIdentifier(), CGGameState::GAME_START));
}

void GameConnection::ConnectPlayer(uint32_t sourceIdentifier, uint32_t targetIdentifier)
{
	Send(new GCArrangedAccept(sourceIdentifier, targetIdentifier));
}

void GameConnection::SpawnPlayer(Player::Ptr player, Spawn spawn)
{
	Send(new GCRespawn(player->GetIdentifier(), player->GetCharacter(), NULL, spawn.x, spawn.y, spawn.z));
}

void GameConnection::RemoveInvincibility(uint32_t target)
{
	SetGameState(CGGameState::REMOVE_INVINCIBILITY, target);
}

void GameConnection::EnableShooting(Player::Ptr player)
{
	Send(new GCWeapon(player->GetIdentifier(), CGWeapon::ENABLE_SHOOTING));
}

void GameConnection::TakeDamage(CGHit hit, uint16_t damage, uint16_t newHealth)
{
	Send(new GCHit(hit, newHealth, damage));
}

void GameConnection::RefillWeapon(uint32_t itemIdentifier)
{
	Send(
		new GCGameItem(
			CGGameItem::REFILL_AMMO,
			std::vector<GCGameItem::Item>({ GCGameItem::Item{GameItem::AMMO_CLIP, 0x01, 0x00, 0x00, 0x00} }),
			itemIdentifier
		)
	);
}

void GameConnection::RefillAllWeapons(Player::Ptr player)
{
	auto session = player->GetSession();

	if (session != nullptr)
	{
		std::array<uint32_t, 4> weapons = session->GetWeapons();

		for (auto weapon : weapons)
		{
			if (weapon != NULL)
			{
				RefillWeapon(weapon);
			}
		}
	}
}

void GameConnection::ForceDisconnect()
{
	//Sends an invalid game event to the client, which destroys the connection.

	Send(new GCPvENpcInit());
}

