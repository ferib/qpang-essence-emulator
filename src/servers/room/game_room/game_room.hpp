#ifndef _GAME_ROOM_HPP
#define _GAME_ROOM_HPP

//std
#include <string>
#include <mutex>
#include <memory>
#include <cstdint>

#include "tickable.hpp"
#include "player.hpp"
#include "room_state.hpp"
#include "game_room_session.hpp"


class GameRoom : public std::enable_shared_from_this<GameRoom>, public Tickable
{
	typedef std::vector<Player::Ptr> player_container;
	typedef std::shared_ptr<GameRoomSession> room_session;

public:

	/**
	 * \brief shorthand usage of the smart pointer
	 */
	using Ptr = std::shared_ptr<GameRoom>;

	/**
	 * \brief construct this gameroom object
	 * \param identifier identifier of the gameroom
	 * \param name name of the gameroom
	 * \param mode mode of the gameroom
	 */
	GameRoom(uint32_t identifier, std::string name, GameMode* mode, uint8_t map);

	/**
	 * \brief destructs this gameroom object 
	 */
	~GameRoom();


	/**
	 * \brief tickable callback
	 */
	void Tick(uint64_t tick);


	/**
	 * \brief adds a player to the gameroom
	 * \param player the player object to add
	 */
	void AddPlayer(Player::Ptr player);

	/**
	 * \brief removes a player from the gameroom
	 * \param player the player object to remove
	 */
	void RemovePlayer(Player::Ptr player);

	/**
	 * \brief kicks a player from the room
	 * \param playerIdentifier
	 * \param cmd
	 */
	void KickPlayer(uint32_t playerIdentifier, uint32_t cmd = 0);

	/**
	 * \brief tries to retrieve the player instance by the GameConnection object, will return a nullptr otherwise
	 * \param gameConnection the GameConnection object which will be matched against the current players
	 * \return std::shared_ptr<Player> | nullptr
	 */
	Player::Ptr GetPlayer(const GameConnection* gameConnection);

	/**
	 * \brief tries to retrieve the player instance by a player identifier, will return a nullptr otherwise.
	 * \param identifier 
	 * \return std::shared_ptr<Player> | nullptr
	 */
	Player::Ptr GetPlayer(uint32_t identifier);

	/**
	 * \brief broadcasts a network event across all players in the gameroom
	 * \param gameEvent the event to broadcast
	 */
	template<typename T, typename... Args>
	void Broadcast(Args... args)
	{
		std::lock_guard<std::mutex> lg(m_playerMx);

		for (auto player : m_players)
		{
			player->Send(new T(args...));
		}
	}

	/**
	 * \brief callback for when player loaded the match
	 */
	void OnPlayerLoaded(Player::Ptr player);

	/**
	 * \brief callback for when player left the match
	 */
	void OnPlayerLeft(Player::Ptr player);

	/**
	 * \brief tries to start the session
	 */
	void Start();

	/**
	 * \brief tries to stop the session
	 */
	void Stop();

	/**
	 * \brief ends the session
	 */
	void End();

	/**
	 * \brief force stops the match, kick everyone, cleanup
	 */
	void Close();

	/**
	 * \brief balances every player in all teams. will try to give the team the same amount of players.. etc. Also takes care of the visual stuff
	 */
	void BalancePlayers();

	/**
	 * \brief returns the team where the player needs to be put in to
	 * \param player 
	 */
	void BalancePlayer(Player::Ptr player);
	
	/**
	 * \brief sets the current map of the gameroom
	 * \param map 
	 */
	void SetMap(uint8_t map);

	/**
	 * \brief sets the current mode of the gameroom
	 * \param gameMode 
	 */
	void SetMode(GameMode* gameMode);

	/**
	 * \brief sets the password of the gameroom
	 * \param password 
	 */
	void SetPassword(std::string password);

	/**
	 * \brief sets the master identifier of the room by player identifier
	 * \param playerIdentifier 
	 */
	void SetNewMaster(uint32_t playerIdentifier);

	/**
	 * \brief sets the new max player count of this room
	 * \param maxPlayerCount 
	 */
	void SetMaxPlayerCount(uint32_t maxPlayerCount);

	/**
	 * \brief sets if skills should be enabled in this room
	 * \param enabled 
	 */
	void SetSkillsEnabled(uint8_t enabled);

	/**
	 * \brief sets if the score that needs to be reached is points or time
	 * \param isPoints 
	 */
	void SetPointsGame(uint8_t isPoints);

	/**
	 * \brief sets the goal in points
	 * \param points 
	 */
	void SetPointsGoal(uint8_t points);

	/**
	 * \brief sets the goal in minutes
	 * \param minutes 
	 */
	void SetTimeGoal(uint8_t minutes);

	/**
	 * \brief broadcasts the right events to make sure you see the player in the game room lobby.
	 * \param player 
	 */
	void AddPlayerToRoom(Player::Ptr player);

	/**
	 * \brief broadcasts the right events to make sure you see the player left the game room lobby
	 * \param player
	 */
	void RemovePlayerFromRoom(Player::Ptr player);

	/**
	 * \brief finds a random player in the room which is eligible to be the new room master. Sets the master identifier
	 * \return uin32_t
	 */
	uint32_t FindNewMaster();

	/**
	 * \brief returns the state of the room
	 * \return RoomState
	 */
	RoomState GetState() const;

	/**
	 * \brief returns the name of the room
	 * \return std::string
	 */
	std::string GetName() const;

	/**
	 * \brief returns the identifier of the room
	 * \return uint32_t
	 */
	uint32_t GetIdentifier() const;

	/**
	 * \brief returns the current mode of the room
	 * \return Mode
	 */
	GameMode* GetMode() const;

	/**
	 * \brief returns the player count of the room
	 * \return uint8_t
	 */
	uint8_t GetPlayerCount();

	/**
	 * \brief returns the identifier of the player that is currently the room master
	 * \return uint32_t
	 */
	uint32_t GetMasterIdentifier() const;

	/**
	 * \brief returns the maximum amount of players that can be in this room
	 * \return uint8_t
	 */
	uint8_t GetMaxPlayerCount() const;

	/**
	 * \brief returns the current map the room is on
	 * \return uint8_t
	 */
	uint8_t GetMap() const;

	/**
	 * \brief returns the current password of the room
	 * \return std::string
	 */
	std::string GetPassword() const;

	/**
	 * \brief returns whether or not this game is points
	 * \return bool
	 */
	bool IsPointsGame() const;

	/**
	 * \brief returns time goal of room (in secs)
	 * \return uin32_t
	 */
	uint32_t GetTimeGoal() const;

	/**
	 * \brief returns point goal of room
	 * \return uint32_t
	 */
	uint32_t GetPointGoal() const;

	GameRoomSession::Ptr GetSession() const;

	/**
	 * \brief returns true when the game is playing
	 * \return bool
	 */
	bool IsPlaying() const;

	/**
	 * \brief returns true when the game is in melee only mode
	 * \return bool
	 */
	bool IsMeleeOnly() const;

	/**
	 * \brief determines if the room has a password lock on it or not
	 * \return bool
	 */
	bool HasPassword() const;

	/**
	 * \brief returns true when the 
	 * \return bool
	 */
	bool HasSkillsEnabled() const;

private:

	/**
	 * \brief inserts a player in the player container
	 * \param player 
	 */
	void InsertPlayer(Player::Ptr player);

	/**
	 * \brief syncs this gameroom with the lobbyserver
	 */
	void Sync();

	/**
	 * \brief the container which takes care of all the players
	 */
	player_container m_players;

	/**
	 * \brief a unique ptr towards a game room session, where all the game logics (outside room) happen.
	 */
	room_session m_session;

	/**
	 * \brief the mutex which takes care of the player container
	 */
	std::mutex m_playerMx;

	/**
	 * \brief the current state of the room
	 */
	RoomState m_state;

	/**
	 * \brief the current game mode of the room
	 */
	GameMode* m_mode;

	/**
	 * \brief the player identifier of the room master
	 */
	uint32_t m_masterIdentifier;

	/**
	 * \brief the maximum amount of players that can be in this room
	 */
	uint8_t m_maxPlayerCount = 8;

	/**
	 * \brief the duration of the game (in minutes)
	 */
	uint8_t m_time = 10;

	/**
	 * \brief the amount of points needed to be scored (if it's a point game)
	 */
	uint8_t m_points = 10;

	/**
	 * \brief determines if the points should be used, or the max game duration
	 */
	uint8_t m_isPointsGame = true;

	/**
	 * \brief the map of the room
	 */
	uint8_t m_map;

	/**
	 * \brief if the room is in melee only mode
	 */
	uint8_t m_meleeOnly = false;

	/**
	 * \brief if the room has skills enabled
	 */
	uint8_t m_skillsEnabled = false;

	/**
	 * \brief the password of the room
	 */
	std::string m_password = "";

	/**
	 * \brief the identifier of this gameroom object
	 */
	const uint32_t m_identifier;

	/**
	 * \brief the name of this gameroom object
	 */
	const std::string m_name;
};

#endif //_GAME_ROOM_HPP