#include "player.hpp"
#include "event_include.hpp"
#include "accounts.hpp"
#include "game.hpp"
#include "game_connection.hpp"
#include "game_room.hpp"
#include "game_item.hpp"
//std
#include <iostream>
#include "cg_score.hpp"
#include "cg_auth.hpp"
#include "gc_score.hpp"
#include "gc_game_state.hpp"
#include "gc_arranged_conn.hpp"
#include "gc_arranged_accept.hpp"
#include "gc_join.hpp"
#include "gc_respawn.hpp"
#include "cg_game_state.hpp"
#include "gc_card.hpp"
#include "gc_weapon.hpp"
#include "gc_game_item.hpp"

Player::Player(GameConnection* netConnection, const uint32_t& identifier)
	: m_connection(netConnection), m_identifier(identifier), m_state(PlayerState::IN_SQUARE)
{
}

Player::~Player() 
{
}

void Player::RefreshSession()
{
	m_session = std::make_shared<PlayerSession>(m_character, GetEquipment()->GetWeapons());
}

void Player::ApplySession()
{
	SetExperience(GetExperience() + m_session->GetExperience());

	m_session.reset();
}

void Player::Send(GameNetEvent* evt) const
{
	try
	{
		if (m_connection->getConnectionState() == NetConnection::Connected)
			m_connection->postNetEvent(evt);
	}
	catch (const std::exception& e)
	{
		sLogger->Get()->error(e.what());
	}

}

GameConnection* Player::GetConnection()
{
	return m_connection;
}

Player::shrd_game_room Player::GetRoom() const
{
	return m_room.expired() ? nullptr : m_room.lock();
}

Player::session Player::GetSession() const
{
	return m_session;
}

uint32_t Player::GetIdentifier() const
{
	return m_identifier;
}

std::string Player::GetName() const
{
	return m_name;
}

Character Player::GetCharacter() const
{
	return m_character;
}

uint32_t Player::GetLevel() const
{
	return m_level;
}

uint32_t Player::GetPrestige() const
{
	return m_prestige;
}

uint8_t Player::GetRank() const
{
	return m_rank;
}

uint32_t Player::GetExperience() const
{
	return m_experience;
}

PlayerState Player::GetState() const
{
	return m_state;
}

Team Player::GetTeam() const
{
	return m_team;
}

Equipment* Player::GetEquipment()
{
	return &m_equipment;
}

bool Player::IsIdle() const
{
	return m_state == PlayerState::IDLING;
}

bool Player::IsReady() const
{
	return m_state == PlayerState::READY || IsPlaying();
}

bool Player::IsPlaying() const
{
	return m_state == PlayerState::IN_GAME || m_state == PlayerState::WAITING_FOR_PLAYERS || m_state == PlayerState::RESULT_SCREEN || m_state == PlayerState::LOADING || m_state == PlayerState::RESULT_SCREEN;
}

bool Player::IsLoading() const
{
	return m_state == PlayerState::LOADING;
}

void Player::SetRoom(const game_room& room)
{
	m_room = room;
}

void Player::SetIdentifier(const uint32_t& identifier)
{
	m_identifier = identifier;
}

void Player::SetName(const std::string& name)
{
	m_name = name;
}

void Player::SetCharacter(const Character& character)
{
	m_character = character;
}

void Player::SetLevel(const uint32_t& level)
{
	m_level = level;
}

void Player::SetPrestige(const uint32_t& prestige)
{
	m_prestige = prestige;
}

void Player::SetRank(const uint8_t& rank)
{
	m_rank = rank;
}

void Player::SetExperience(const uint32_t& experience)
{
	m_experience = experience;
}

void Player::SetState(const PlayerState& state)
{
	m_state = state;
}

void Player::SetTeam(const Team& team)
{
	m_team = team;
}

void Player::UnsetRoom()
{
	m_room.reset();
}

void Player::HandleEvent(GameNetEvent::Ptr & evt)
{

}
