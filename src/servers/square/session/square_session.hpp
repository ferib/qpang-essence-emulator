#ifndef _SQUARE_SESSION_H
#define _SQUARE_SESSION_H

#include <net/session.hpp>
#include "info_manager.hpp"
#include "chat_response_event.hpp"
#include <memory>
#include <cstdint>

class Square;
class SquareManager;
class SquarePacketHandler;

class SquareSession : public Session, public std::enable_shared_from_this<SquareSession>
{

public:
	using Ptr = std::shared_ptr<SquareSession>;
	SquareSession(Connection::Ptr connection);
	~SquareSession();
	void HandlePacket(ClientPacket& packet);
	void HandleClose();

	SquarePacketHandler* handler;
	inline uint32_t GetPlayerId() { return _playerId; };
	inline void SetPlayerId(uint32_t playerId) { _playerId = playerId; };

	inline SquareManager* GetSquareManager() { return _manager; };
	inline void SetManager(SquareManager* manager) { _manager = manager; };

	inline InfoManager* Info() { return _infoManager; };

	inline void SetSquare(std::weak_ptr<Square> square) { _square = square; };
	std::shared_ptr<Square> GetSquare() { return _square.lock(); };

	void Whisper(std::string message);
private:
	uint32_t _playerId;
	SquareManager* _manager;
	InfoManager* _infoManager;
	std::weak_ptr<Square> _square;

};


#endif //_SQUARE_SESSION_H