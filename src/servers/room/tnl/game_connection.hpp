#ifndef GAMECONNECTION_HPP
#define GAMECONNECTION_HPP

//tnl
#include <tnl/tnl.h>
#include <tnl/tnlEventConnection.h>

//std
#include <string>
#include <memory>

#include "game_room.hpp"
#include "spawn.hpp"

using namespace TNL;

class CGHit;

class GameConnection : public EventConnection
{
	typedef NetConnection Parent;
	friend class GameNetInterface;

public:
	GameConnection();
	void onConnectionEstablished() override;

	void onConnectionTerminated(TerminationReason, const char*) override;
	void onConnectTerminated(TerminationReason, const char*) override;


	void SetGameState(uint32_t cmd, uint32_t playerIdentifier = 0, uint32_t value = 0, uint32_t valueIdentifier = 0);
	void OnPlayerChange(Player::Ptr player, uint32_t cmd = 0, uint32_t value = 0);
	void CreateRoom(uint32_t playerId, uint8_t cmd, GameRoom::Ptr room);
	void SetRoomInfo(GameRoom::Ptr room);
	void AddPlayerToRoom(Player::Ptr player);
	void KickPlayer(uint32_t playerIdentifier, uint32_t masterIdentifier, uint32_t cmd);

	void SetPlayerTeam(Player::Ptr player, Team team);
	void SendPlayerMessage(uint32_t playerIdentifier, std::wstring nickname, std::wstring message);

	void EnterGame(Player::Ptr player);

	void ConnectPlayer(uint32_t sourceIdentifier, uint32_t targetIdentifier);
	void SpawnPlayer(Player::Ptr player, Spawn spawn);
	void RemoveInvincibility(uint32_t target);
	void EnableShooting(Player::Ptr player);

	void TakeDamage(CGHit hit, uint16_t damage, uint16_t newHealth);
	void RefillWeapon(uint32_t itemIdentifier);
	void RefillAllWeapons(Player::Ptr player);

	void ForceDisconnect();

	uint32_t playerId;

	TNL_DECLARE_NETCONNECTION(GameConnection);

private:
	void Send(GameNetEvent* theEvent)
	{
		try
		{
			if (getConnectionState() == NetConnection::Connected && theEvent != nullptr)
				postNetEvent(theEvent);
		}
		catch (const std::exception& e)
		{
			sLogger->Get()->error(e.what());
		}
	}
};

#endif //GAMECONNECTION_HPP