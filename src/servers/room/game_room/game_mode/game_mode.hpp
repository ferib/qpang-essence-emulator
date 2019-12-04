#ifndef _GAME_MODE_HPP
#define _GAME_MODE_HPP

#include "player.hpp"
#include "player_session.hpp"
#include "spawn.hpp"

//std
#include <string>
#include <memory>
#include <vector>

class GameRoomSession;

class GameMode : public std::enable_shared_from_this<GameMode>
{
public:
	GameMode();
	~GameMode();

	/**
	 * \brief callback used when this gamemode got set in the gameroom.. normally used for resetting player teams, etc.
	 * \param room 
	 */
	virtual void OnApply(const std::shared_ptr<GameRoom>& room);

	/**
	 * \brief callback when the 'waiting for players' screen is over
	 * \param roomSession
	 */
	virtual void OnStart(const std::shared_ptr<GameRoomSession>& roomSession);

	/**
	 * \brief callback when a player joins the match
	 * \param playerSession
	 */
	virtual void OnPlayerMidGameJoin(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player);

	/**
	 * \brief callback when a player joins the match
	 * \param playerSession 
	 */
	virtual void OnPlayerLoaded(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player);

	/**
	 * \brief callback when a player instance starts a game (after WFP)
	 * \param player 
	 */
	virtual void OnPlayerStart(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player);

	/**
	 * \brief callback when a player leaves the match (while it's playing)
	 * \param playerSession 
	 */
	virtual void OnPlayerLeave(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player);

	/**
	 * \brief callback when a player got killed while in a match
	 * \param killerSession 
	 * \param targetSession 
	 */
	virtual void OnPlayerKill(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& killer, const Player::Ptr& target);

	/**
	 * \brief callback when a player respawns
	 * \param playerSession 
	 * \param spawn 
	 */
	virtual void OnPlayerSpawn(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player, const Spawn& spawn);

	/**
	 * \brief callback when a player activates a skill.. TODO: Add skill parameter
	 * \param playerSession 
	 */
	virtual void OnPlayerSkill(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr& player) {};

	/**
	 * \brief callback for when the gameroom has to sync the score
	 * \param room 
	 */
	virtual void OnCheckScore(GameRoom* room);

	/**
	 * \brief callback when the game finishes, perhaps it needs to save additional data..
	 * \param room 
	 */
	virtual void OnSave(const std::shared_ptr<GameRoomSession>& session);

	/**
	 * \brief determines whether or not everyone should leave their teams or not etc..
	 * \return bool
	 */
	virtual bool IsTeamMode();

	/**
	 * \brief returns the name of this gamemode.
	 * \return std::string
	 */
	virtual std::string GetName();

	/**
	 * \brief 
	 * \return uint8_t
	 */
	virtual uint8_t GetModeIdentifier();


private:
	uint8_t m_modeIdentifier;
	std::string m_name;
};

#endif //_GAME_MODE_HPP