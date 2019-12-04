#include "player_session.hpp"
#include <algorithm>

PlayerSession::PlayerSession(uint16_t character, std::array<uint32_t, 4> weapons) :
	m_character(character),
	m_weapons(weapons),
	m_weapon(0),
	m_kills(0),
	m_deaths(0),
	m_streak(0),
	m_coins(0),
	m_don(0),
	m_cash(0),
	m_experience(0),
	m_invincible(false)
{
	for (auto weapon : m_weapons)
	{
		if (weapon != NULL)
		{
			m_weapon = weapon;
			break;
		}
	}
}

void PlayerSession::AddKill()
{
	m_kills++;
}

void PlayerSession::AddDeath()
{
	m_deaths++;
}

void PlayerSession::AddStreak()
{
	m_streak++;
}

void PlayerSession::AddCoins(uint32_t coins)
{
	m_coins += coins;
}

void PlayerSession::AddDon(uint32_t don)
{
	m_don += don;
}

void PlayerSession::AddCash(uint32_t cash)
{
	m_cash += cash;
}

void PlayerSession::AddExperience(uint32_t experience)
{
	m_experience += experience;
}

void PlayerSession::AddHealth(uint16_t health)
{
	m_health += health;
}

void PlayerSession::DepleteHealth(uint16_t health)
{
	if (health > m_health)
	{
		m_health = 0;
		return;
	}

	m_health -= health;
}

void PlayerSession::ResetHealth()
{
	m_health = GetDefaultHealth();
}

void PlayerSession::SetWeapon(uint32_t weaponIdentifier)
{
	m_weapon = weaponIdentifier;
}

void PlayerSession::SetInvincible(bool invincible)
{
	m_invincible = invincible;
}

uint32_t PlayerSession::GetKills() const
{
	return m_kills;
}

uint32_t PlayerSession::GetDeaths() const
{
	return m_deaths;
}

uint32_t PlayerSession::GetStreak() const
{
	return m_streak;
}

uint32_t PlayerSession::GetCoins() const
{
	return m_coins;
}

uint32_t PlayerSession::GetDon() const
{
	return m_don;
}

uint32_t PlayerSession::GetCash() const
{
	return m_cash;
}

uint32_t PlayerSession::GetExperience() const
{
	return m_experience;
}

uint16_t PlayerSession::GetHealth() const
{
	return m_health;
}

uint16_t PlayerSession::GetDefaultHealth() const
{
	uint16_t health = 0;

	switch (m_character)
	{
	case 579:
		health = 90;
		break;
	case 578:
		health = 200;
		break;
	case 850:
		health = 130;
		break;
	case 851:
		health = 150;
		break;
	case 333:
	case 343:
	default:
		health = 100;
		break;
	}

	return health;
}

uint16_t PlayerSession::GetCharacter() const
{
	return m_character;
}

uint32_t PlayerSession::GetWeapon() const
{
	return m_weapon;
}

std::array<uint32_t, 4> PlayerSession::GetWeapons() const
{
	return m_weapons;
}

bool PlayerSession::HasConnection(const uint32_t & connectionIdentifier)
{
	std::lock_guard<std::mutex> lg(m_connectionMx);

	return m_connections.find(connectionIdentifier) != m_connections.end();
}

void PlayerSession::AddConnection(const uint32_t & connectionIdentifier)
{
	std::lock_guard<std::mutex> lg(m_connectionMx);

	m_connections.insert(connectionIdentifier);
}

bool PlayerSession::HasWeapon(const uint32_t & weaponIdentifier)
{
	auto result = std::find(m_weapons.begin(), m_weapons.end(), weaponIdentifier);

	return result != m_weapons.end();
}

bool PlayerSession::IsInvincible()
{
	return m_invincible;
}

void PlayerSession::ResetStreak()
{
	m_streak = 0;
}

void PlayerSession::Reset()
{
	ResetStreak();
	m_kills = 0;
	m_deaths = 0;
	m_coins = 0;
	m_don = 0;
	m_cash = 0;
	m_experience = 0;
}
