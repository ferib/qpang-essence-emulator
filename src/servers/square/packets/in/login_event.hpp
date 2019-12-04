#ifndef LOGIN_EVENT_HPP
#define LOGIN_EVENT_HPP

#include "square_packet_event.hpp"
#include "request_equipment_event.hpp"
#include "square_session.hpp"
#include "square_manager.hpp"

class LoginEvent : public SquarePacketEvent {

public:
	LoginEvent() : SquarePacketEvent(sizeof(Packets::Square::Login)) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Square::Login>();
		sLogger->Get()->debug("Login event: {0:d} is trying to login to squareserver", packet.uid);

		session->SetPlayerId(packet.uid);
		auto lobby = session->GetSquareManager()->LobbyServer();

		lobby->SendPacket(RequestEquipmentEvent{ packet.uid }.Compose(session));
	}
};

#endif