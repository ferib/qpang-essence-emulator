#ifndef ANNOUNCEMENT_EVENT_HPP
#define ANNOUNCEMENT_EVENT_HPP

#include <cstdint>
#include "square_packet_event.hpp"
#include "string_converter.hpp"
#include "packet_data.hpp"

class AnnouncementEvent : public SquarePacketEvent {

public:
	AnnouncementEvent(std::string message) { _message = message; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Internal::Announcement rsp{};
		wcsncpy(rsp.message, std::wstring(_message.begin(), _message.end()).data(), 254);
		return ServerPacket::Create<Opcode::ANNOUNCEMENT>(rsp);
	}
private:
	std::string _message;
};

#endif