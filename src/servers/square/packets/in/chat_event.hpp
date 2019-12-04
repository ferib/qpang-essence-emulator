#ifndef CHAT_EVENT_HPP
#define CHAT_EVENT_HPP

#include "packet.hpp"
#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include "square_session.hpp"
#include "square.hpp"
#include <vector>
#include "chat_response_event.hpp"
#include "string_converter.hpp"

class ChatEvent : public SquarePacketEvent {

public:
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		pack.buffer.resize(sizeof(Packets::Square::ParkPlayerChat) + pack.buffer.size() - 36); // 36 = length before message starts. resizing because buffer size is dynamic
		auto packet =  pack.Read<Packets::Square::ParkPlayerChat>();
		auto square = session->GetSquare();

		std::string message = StringConverter::WcharToString(packet.message, packet.messageLength % 254);
		message.resize(packet.messageLength);
		uint32_t senderId = session->Info()->Id();

		if (!square)
		{
			sLogger->Get()->warn("ChatEvent: {0} tried sending a chat when he is not in a square", session->Info()->Nickname());
			return;
		}

		sLogger->Get()->info("{0}: {1}", session->Info()->Nickname(), message);
		if (session->GetSquareManager()->HandleMessage(session, message))
		{
			square->SendPacket(ChatResponseEvent{ session->Info()->Nickname(), message }.Compose(session));
		}
	}
};

#endif