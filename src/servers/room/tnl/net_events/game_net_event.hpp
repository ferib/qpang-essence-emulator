#ifndef _GAME_NET_EVENT_HPP
#define _GAME_NET_EVENT_HPP

#include <tnl/tnl.h>
#include <tnl/tnlBitStream.h>
#include <tnl/tnlNetEvent.h>
#include <tnl/tnlByteBuffer.h>

#include "game_net_id.hpp"

//std
#include <string>
#include <cstdint>
#include <memory>

//so we don't have to write TNL::U32/etc everytime
using namespace TNL;

//fwd
class GameConnection;
class Player;

#define NET_POST_EVENT(gameConn) auto __evt = std::make_shared<std::remove_pointer_t<decltype(this)>>(*this); \
	__evt->gameConnection = reinterpret_cast<GameConnection*>(gameConn); \
	sGame->PostEvent(__evt)

class GameNetEvent : public NetEvent
{
public:
	using Ptr = std::shared_ptr<GameNetEvent>;
	GameNetEvent();
	GameNetEvent(GameNetId gameNetId, 
		NetEvent::GuaranteeType guaranteeType, 
		NetEvent::EventDirection eventDirection);
	GameNetEvent(GameConnection*,
		GameNetId gameNetId, NetEvent::GuaranteeType guaranteeType, NetEvent::EventDirection eventDirection);

	std::wstring GetString(ByteBuffer* buffer);
	void WriteBuffer(BitStream* buffer, std::string data);
	void WriteBuffer(BitStream* buffer, std::wstring data);
	std::wstring ReadBuffer(BitStream* stream);

	virtual void handle(std::shared_ptr<Player> player) {};

	GameNetId id;
	GameConnection* gameConnection;
};

#endif //GAMENETEVENT_HPP