#ifndef _PLAYER_HPP
#define _PLAYER_HPP

//std
#include <cstdint>
#include <memory>

#include "character.hpp"
#include "game_net_event.hpp"
#include "tickable.hpp"
#include "equipment.hpp"
#include "player_state.hpp"
#include "player_session.hpp"
#include "team.hpp"

class GameRoom;

class Player
{

	typedef std::weak_ptr<GameRoom> game_room;
	typedef std::shared_ptr<GameRoom> shrd_game_room;
	typedef PlayerSession::Ptr session;

public:

	/**
	 * \brief shorthand usage of the smart pointer
	 */
	using Ptr = std::shared_ptr<Player>;

	/**
	 * \brief constructs this player object
	 * \param netConnection 
	 * \param identifier 
	 */
	Player(GameConnection* netConnection, const uint32_t& identifier);

	/**
	 * \brief destructs this player object
	 */
	~Player();

	/**
	 * \brief resets the current player session
	 */
	void RefreshSession();

	/**
	 * \brief grabs all the properties of this player's game, and applies it to it's global properties. also clears the session's properties
	 */
	void ApplySession();

	/**
	 * \brief callback when the NET_POST_EVENT macro is used in an event
	 * \param evt 
	 */
	void HandleEvent(GameNetEvent::Ptr& evt);

	/**
	 * \brief sends an event to the connected gameconnection
	 * \param evt 
	 */
	void Send(GameNetEvent* evt) const;

	/**
	 * \brief returns the corresponding gameconnection to this player object
	 * \return GameConnection* 
	 */
	GameConnection* GetConnection();

	/**
	 * \brief returns the current room where the player is in
	 * \return std::shared_ptr<GameRoom>
	 */
	shrd_game_room GetRoom() const;

	/**
	 * \brief returns the shared pointer pointing to a PlayerSession object
	 * \return std::shared_ptr<PlayerSession> 
	 */
	session GetSession() const;

	/**
	 * \brief returns the identifier of this player object
	 * \return uint32_t
	 */
	uint32_t GetIdentifier() const;

	/**
	 * \brief returns the name of this player object
	 * \return std::string
	 */
	std::string GetName() const;

	/**
	 * \brief returns the character of this player object
	 * \return Character
	 */
	Character GetCharacter() const;

	/**
	 * \brief returns the level of this player object
	 * \return uint32_t
	 */
	uint32_t GetLevel() const;

	/**
	 * \brief returns the prestige of this player object
	 * \return uint32_t
	 */
	uint32_t GetPrestige() const;

	/**
	 * \brief returns the rank of this player object
	 * \return uint8_t
	 */
	uint8_t GetRank() const;

	/**
	 * \brief returns the experience amount of this player object
	 * \return uint32_t
	 */
	uint32_t GetExperience() const;

	/**
	 * \brief returns the current state of this player object
	 * \return PlayerState
	 */
	PlayerState GetState() const;

	/**
	 * \brief returns the current team of this player object
	 * \return Team
	 */
	Team GetTeam() const;

	/**
	 * \brief returns a pointer to the equipment instance of the player's equipment
	 * \return Equipment*
	 */
	Equipment* GetEquipment();

	/**
	 * \brief returns true when the player is idle in the gameroom
	 * \return bool
	 */
	bool IsIdle() const;

	/**
	 * \brief returns true when the player is either ready in the gameroom, or playing in the game
	 * \return bool
	 */
	bool IsReady() const;

	/**
	 * \brief returns true when the player is playing the game
	 * \return bool
	 */
	bool IsPlaying() const;

	/**
	 * \brief return true when the player is in the loading screen
	 * \return bool
	 */
	bool IsLoading() const;

	/**
	 * \brief sets the reference of the room the current player is in
	 * \param room 
	 */
	void SetRoom(const game_room& room);

	/**
	 * \brief sets the player's identifier
	 * \param identifier 
	 */
	void SetIdentifier(const uint32_t& identifier);

	/**
	 * \brief sets the player's name
	 * \param name 
	 */
	void SetName(const std::string& name);

	/**
	 * \brief sets the player's currently selected character
	 * \param character 
	 */
	void SetCharacter(const Character& character);

	/**
	 * \brief sets the player's level
	 * \param level 
	 */
	void SetLevel(const uint32_t& level);

	/**
	 * \brief sets the player's prestige
	 * \param prestige 
	 */
	void SetPrestige(const uint32_t& prestige);

	/**
	 * \brief sets the player's rank
	 * \param rank 
	 */
	void SetRank(const uint8_t& rank);

	/**
	 * \brief sets the player's experience
	 * \param experience 
	 */
	void SetExperience(const uint32_t& experience);

	/**
	 * \brief sets the player's current state
	 * \param state 
	 */
	void SetState(const PlayerState& state);

	/**
	 * \brief sets the player's current team
	 * \param team 
	 */
	void SetTeam(const Team& team);

	/**
	 * \brief resets the room's weak ptr
	 */
	void UnsetRoom();

private:

	/**
	 * \brief the corresponding gameconnection attached to this player object
	 */
	GameConnection* m_connection;

	/**
	 * \brief a weak pointer to the room the player is currently in (if the player is)
	 */
	game_room m_room;

	/**
	 * \brief a shared pointer to the player session, which is refreshed when the player loads a game
	 */
	session m_session;

	/**
	 * \brief the identifier of this player object
	 */
	uint32_t m_identifier;

	/**
	 * \brief the name of this player object
	 */
	std::string m_name;

	/**
	 * \brief the current selected character of this player object
	 */
	Character m_character;

	/**
	 * \brief the level of this player object
	 */
	uint32_t m_level;

	/**
	 * \brief the prestige of this player object
	 */
	uint32_t m_prestige;

	/**
	 * \brief the rank of this player object
	 */
	uint8_t m_rank;

	/**
	 * \brief the experience amount of this player object
	 */
	uint32_t m_experience;

	/**
	 * \brief the current state of this player object
	 */
	PlayerState m_state;

	/**
	 * \brief the equipment container of this player object
	 */
	Equipment m_equipment;

	/**
	 * \brief the team the player is currently in
	 */
	Team m_team;
};

#endif //_PLAYER_HPP