#ifndef PLAYER_SESSION_HPP
#define PLAYER_SESSION_HPP

#include <memory>
#include <cstdint>
#include <array>
#include <set>
#include <mutex>

class PlayerSession : std::enable_shared_from_this<PlayerSession>
{

	typedef std::set<uint32_t> connection_container;

public:

	using Ptr = std::shared_ptr<PlayerSession>;

	/**
	 * \brief constructor of the player session
	 */
	PlayerSession(uint16_t character, std::array<uint32_t, 4> weapons);

	/**
	 * \brief destructor of the player session (unused)
	 */
	~PlayerSession() = default;

	/**
	 * \brief Add one kill to the current session
	 */
	void AddKill();

	/**
	 * \brief Add one death to the current session
	 */
	void AddDeath();

	/**
	 * \brief Add one kill to the kill streak
	 */
	void AddStreak();

	/**
	 * \brief Add X amount of coins to the current session
	 * \param coins 
	 */
	void AddCoins(uint32_t coins);

	/**
	 * \brief Add X amount of don to the current session
	 * \param don 
	 */
	void AddDon(uint32_t don);

	/**
	 * \brief Add X amount of cash to the current session
	 * \param cash 
	 */
	void AddCash(uint32_t cash);

	/**
	 * \brief Add X amount of experience to the current session
	 * \param experience 
	 */
	void AddExperience(uint32_t experience);

	/**
	 * \brief Add X amount of health
	 * \param health
	 */
	void AddHealth(uint16_t health);

	/**
	 * \brief Remove X amount of health
	 * \param health
	 */
	void DepleteHealth(uint16_t health);

	/**
	 * \brief resets health to default
	 */
	void ResetHealth();

	/**
	 * \brief set player's weapon
	 * \param health
	 */
	void SetWeapon(uint32_t weaponIdentifier);

	/**
	 * \brief set player's invincible state
	 * \param invincible = true
	 */
	void SetInvincible(bool invincible = true);

	/**
	 * \brief returns the amount of kills this session has
	 * \return uint32_t
	 */
	uint32_t GetKills() const;

	/**
	 * \brief returns the amount of deaths this session has
	 * \return uint32_t
	 */
	uint32_t GetDeaths() const;

	/**
	 * \brief returns the current streak this session has
	 * \return uint32_t
	 */
	uint32_t GetStreak() const;

	/**
	 * \brief returns the amount of coins this session has
	 * \return uint32_t
	 */
	uint32_t GetCoins() const;

	/**
	 * \brief returns the amount of don this session has
	 * \return uint32_t
	 */
	uint32_t GetDon() const;

	/**
	 * \brief returns the amount of cash this session has
	 * \return uint32_t
	 */
	uint32_t GetCash() const;

	/**
	 * \brief returns the amount of experience this session has
	 * \return uint32_t
	 */
	uint32_t GetExperience() const;

	/**
	 * \brief returns the amount of experience this session has
	 * \return uint16_t
	 */
	uint16_t GetHealth() const;

	/**
	* \brief returns the default health according to 
	* \return uint16_t
	*/
	uint16_t GetDefaultHealth() const;

	/**
	 * \brief return the character for this session
	 * \return uint16_t
	 */
	uint16_t GetCharacter() const;

	/**
	 * \brief return the weapon for this session
	 * \return uint32_t
	 */
	uint32_t GetWeapon() const;

	/**
	 * \brief retyrns all the weapons for this session
	 * \return std::array<uint32_t, 4>
	 */
	std::array<uint32_t, 4> GetWeapons() const;

	/**
	 * \brief checks if player is already 'connected' to x player
	 * \return bool
	 */
	bool HasConnection(const uint32_t& connectionIdentifier);

	/**
	 * \brief adds a conenction to the connection table
	 */
	void AddConnection(const uint32_t& connectionIdentifier);

	/**
	 * \brief checks if player can switch to this weapon
	 */
	bool HasWeapon(const uint32_t& weaponIdentifier);

	/**
	 * \brief returns true if player invincible
	 */
	bool IsInvincible();

	/**
	 * \brief resets the current (kill)streak this session has
	 */
	void ResetStreak();

	/**
	 * \brief resets every property this session has
	 */
	void Reset();

private:

	uint32_t m_kills;
	uint32_t m_deaths;
	uint32_t m_streak;
	uint32_t m_coins;
	uint32_t m_don;
	uint32_t m_cash;
	uint32_t m_experience;
	uint16_t m_health;
	uint16_t m_character;
	uint32_t m_weapon;
	bool m_invincible;

	std::mutex m_connectionMx;
	connection_container m_connections;
	std::array<uint32_t, 4> m_weapons;
};

#endif