#ifndef CHAT_RESPONSE_EVENT_HPP
#define CHAT_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <string>
#include <cstdint>
#include "string_converter.hpp"

class ChatResponseEvent : public SquarePacketEvent {

public:
	ChatResponseEvent(std::string sender, std::string message) { _sender = sender; _message = message; };

	ServerPacket Compose(SquareSession* session) override {
		Packets::Square::ParkPlayerChatRsp rsp{};
		wcsncpy(rsp.sender, std::wstring(_sender.begin(), _sender.end()).data(), 16);
		wcsncpy(rsp.message, std::wstring(_message.begin(), _message.end()).data(), 254);
		rsp.length = _message.size();
		return ServerPacket::Create<Opcode::SQUARE_CHAT_RSP>(rsp);
	};
private:
	std::string _sender;
	std::string _message;
};

#endif