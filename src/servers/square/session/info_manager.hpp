#ifndef INFO_MANAGER_HPP
#define INFO_MANAGER_HPP

#include <cstdint>
#include <array>
#include <string>

class InfoManager {

public:

	void SetEquipment(std::array<uint32_t, 9> equipment);
	std::array<uint32_t, 9> Equipment();

	void SetId(uint32_t id);
	uint32_t Id();
	void SetRank(uint8_t rank);
	uint8_t Rank();
	void SetLevel(uint32_t level);
	uint32_t Level();
	void SetPrestige(uint32_t prestige);
	uint32_t Prestige();
	void SetCharacter(uint16_t character);
	uint16_t Character();
	void SetNickname(std::string name);
	std::string Nickname();
	void SetPosition(std::array<float, 3> position);
	std::array<float, 3> Position();
	void SetState(uint32_t state);
	uint32_t State();
private:
	std::string _nickname;
	uint32_t _playerId;
	uint8_t _rank;
	uint32_t _level;
	uint32_t _prestige;
	uint16_t _character;
	uint32_t _state;
	std::array<uint32_t, 9> _equipment;
	std::array<float, 3> _position;
};

#endif // !INFO_MANAGER_HPP
