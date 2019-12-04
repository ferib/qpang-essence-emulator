#ifndef LOGIN_ERROR_EVENT_HPP
#define LOGIN_ERROR_EVENT_HPP

#include "packet_event.hpp"
#include "packet_data.hpp"
#include "handshake_response_event.hpp"

class LoginErrorEvent : public PacketEvent {

public:
	LoginErrorEvent(uint16_t errCode) { _errCode = errCode; };

	ServerPacket Compose(Connection::Ptr conn) override {
		return ServerPacket::CreateErrorPacket<Opcode::AUTH_LOGIN_FAIL>(_errCode);
	};

private:
	uint16_t _errCode;
};

#endif