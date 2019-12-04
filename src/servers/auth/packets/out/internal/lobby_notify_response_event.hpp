#ifndef LOBBY_NOTIFY_RESPONSE_EVENT_HPP
#define LOBBY_NOTIFY_RESPONSE_EVENT_HPP

#include <boost/lexical_cast.hpp>
#include <cstdint>
#include <array>
#include "database.hpp"
#include "packet_event.hpp"
#include "packet_data.hpp"



class LobbyNotifyResponseEvent : public PacketEvent {

public:
	LobbyNotifyResponseEvent(uint32_t userId, std::array<uint8_t, 16> uuid) { _userId = userId; _uuid = uuid; };

	ServerPacket Compose(Connection::Ptr conn) override {
		Packets::Auth::LobbyNotifyRsp notifyResponse{};
		notifyResponse.userId = _userId;
		notifyResponse.uuid = _uuid;
		notifyResponse.valid = _userId != NULL ? true : false;
		return ServerPacket::Create<Opcode::LOBBY_NOTIFY_RSP>(notifyResponse);
	};

private:
	uint32_t _userId;
	std::array<uint8_t, 16> _uuid;
};

#endif