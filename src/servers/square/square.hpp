#ifndef _SQUARE_HPP
#define _SQUARE_HPP

#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include "packet.hpp"

class SquareSession;

class Square : public std::enable_shared_from_this<Square>
{
public:

	using Ptr = std::shared_ptr<Square>;
	Square();
	Square(uint32_t id, std::string name, uint32_t maxCapacity);
	~Square();

	void SendPacket(ServerPacket pack, uint32_t playerId = 0);

	bool AddPlayer(std::shared_ptr<SquareSession> session);
	void RemovePlayer(uint32_t playerId);
	std::shared_ptr<SquareSession> GetPlayer(uint32_t playerId);
	std::vector<std::shared_ptr<SquareSession>> List();

	inline uint32_t MaxCapacity() { return _maxCapacity; };
	inline uint32_t Size() { return _sessions.size(); }
	inline uint8_t State() { return _state; };
	inline std::string Name() { return _name; };
	inline uint32_t Id() { return _id; };
private:
	uint32_t _id;
	uint32_t _maxCapacity;
	uint8_t _state = 8;
	std::string _name;
	std::vector<std::shared_ptr<SquareSession>> _sessions;
};

#endif