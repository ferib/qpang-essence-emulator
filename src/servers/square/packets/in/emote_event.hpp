#ifndef EMOTE_EVENT
#define EMOTE_EVENT

#include "packet.hpp"
#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include "square_session.hpp"
#include "square.hpp"
#include <vector>
#include "emote_response_event.hpp"
#include "string_converter.hpp"

class EmoteEvent : public SquarePacketEvent {

public:
	EmoteEvent() : SquarePacketEvent(10) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Square::ParkPlayerEmote>();
		sLogger->Get()->debug("Emote event: {0} used emote {1:d}", session->Info()->Nickname(), packet.emoteId);
		session->GetSquare()->SendPacket(EmoteResponseEvent{ session->Info()->Id(), packet.emoteId }.Compose(session));
	}
};

#endif