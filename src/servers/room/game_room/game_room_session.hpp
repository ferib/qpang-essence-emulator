#ifndef GAME_ROOM_SESSION_HPP
#define GAME_ROOM_SESSION_HPP

#include <memory>
#include <cstdint>
#include <vector>
#include <mutex>

#include "player.hpp"
#include "game_mode.hpp"
#include "player_spawner.hpp"
#include "game_item_manager.hpp"

#include "weapon.hpp"
#include "score_board.hpp"

//Relayed events

class CGMove;
class CGShoot;
class CGMotion;
class CGCard;
class CGWeapon;
class CGHit;

class GameRoomSession : public std::enable_shared_from_this<GameRoomSession>, public Tickable
{

	typedef std::vector<Player::Ptr> player_container;
	typedef std::unique_ptr<PlayerSpawner> player_spawner;
	typedef std::unique_ptr<GameItemManager> item_manager;

	enum State : uint8_t {
		WAITING,
		PLAYING,
		FINISHING,
		ENDED,
	};

public:

	using Ptr = std::shared_ptr<GameRoomSession>;

	GameRoomSession(GameMode* mode, uint8_t map, uint32_t goal, bool isPoints);
	~GameRoomSession() = default;
	
	void Intitialize();

	void Tick(uint64_t tick);

	void AddPlayer(Player::Ptr player);
	void RemovePlayer(Player::Ptr player);

	void OnPlayerLoaded(Player::Ptr player);

	template<typename T, typename... Args>
	void Relay(Args... args)
	{
		std::lock_guard<std::recursive_mutex> lg(m_playerMx);

		for (auto player : m_players)
		{
			player->Send(new T(args...));
		}
	}

	void RelayMove(CGMove move);
	void RelayShoot(CGShoot shoot);
	void RelayMotion(CGMotion motion);
	void RelayAbility(CGCard card);
	void RelayWeapon(CGWeapon weapon);
	void RelayHit(CGHit hit, uint16_t damage, uint16_t newHealth, uint16_t streak);

	void KillPlayer(Player::Ptr killer, Player::Ptr target, uint32_t itemIdentifier, bool isHeadshot = false);

	void Start();
	void Stop();
	void End();
	void Clear();

	void ShowStart();

	void InitPlayers();
	void InitPlayer(Player::Ptr player);

	void SpawnPlayers();
	void SpawnPlayer(Player::Ptr player);
	void SpawnPlayersFor(Player::Ptr player);
	void StartRespawning(Player::Ptr player, uint8_t seconds);

	void RemoveInvincibility(uint32_t targetId);

	void AddKillfeed(uint32_t killerIdentifier, uint32_t targetIdentifier, uint32_t weaponIdentifier, bool isHeadshot = false);
	
	ScoreBoard GenerateScoreBoard();

	State GetState();

private:

	void Load();

	bool CanStart();

	void LoadForBoth(Player::Ptr player1, Player::Ptr player2);

	void AddPlayerTo(Player::Ptr player, Player::Ptr playerToAdd);

	void ConnectPlayerTo(Player::Ptr player, Player::Ptr playerToConnect);

	/**
	 * \brief 
	 */
	std::recursive_mutex m_playerMx;

	/**
	 * \brief 
	 */
	player_container m_players;

	/**
	 * \brief 
	 */
	GameMode* m_mode;

	/**
	 * \brief
	 */
	State m_state;

	/**
	 * \brief
	 */
	player_spawner m_playerSpawner;

	/**
	 * \brief 
	 */
	item_manager m_itemManager;

	/**
	 * \brief
	 */
	uint8_t m_map;

	/**
	 * \brief
	 */
	uint32_t m_goal;

	/**
	 * \brief
	 */
	bool m_isPoints;

	
};

#endif