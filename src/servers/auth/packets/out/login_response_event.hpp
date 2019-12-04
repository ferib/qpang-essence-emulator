#ifndef LOGIN_RESPONSE_EVENT_HPP
#define LOGIN_RESPONSE_EVENT_HPP

#include <cstdint>
#include <array>

#include "auth_manager.hpp"
#include "packet_event.hpp"
#include "packet_data.hpp"

class LoginResponseEvent : public PacketEvent {

public:
	LoginResponseEvent(std::array<uint8_t, 16> uuid, uint32_t lobbyHost) { _uuid = uuid; _lobbyHost = lobbyHost; };

	ServerPacket Compose(Connection::Ptr conn) override {
		Packets::Auth::LoginRsp loginResponse;
		loginResponse.uuid = _uuid;
		loginResponse.lobbyServerIp = _lobbyHost;
		return ServerPacket::Create<Opcode::AUTH_LOGIN_RSP>(loginResponse);
	};

private:
	std::array<uint8_t, 16> _uuid;
	uint32_t _lobbyHost;
};

#endif