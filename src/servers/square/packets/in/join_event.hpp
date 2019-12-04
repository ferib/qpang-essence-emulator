#ifndef JOIN_EVENT_HPP
#define JOIN_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_manager.hpp"
#include "join_response_event.hpp"
#include <memory>

//THIS IS THE EVENT WHICH IS GETTING FIRED IF PLAYER WANTS TO JOIN A SQUARE.
class JoinEvent : public SquarePacketEvent {

public:
	JoinEvent() : SquarePacketEvent(sizeof(Packets::Square::ParkJoin)) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Square::ParkJoin>();
		
		std::shared_ptr<Square> square = session->GetSquare();
		sLogger->Get()->debug("Join event: {0} is joining square {1:d}", session->Info()->Nickname(), packet.parkId);

		if (square != nullptr)
		{
			if(square->Id() == packet.parkId)
				return session->SendError<Opcode::SQUARE_JOIN_PARK_FAIL>(1403);

			square->RemovePlayer(packet.uid);
			square = session->GetSquareManager()->GetSquare(packet.parkId);
		}

		if (square == nullptr)
		{
			sLogger->Get()->debug("Join event: Getting available square");
			square = session->GetSquareManager()->GetAvailableSquare();
		}


		if (square->AddPlayer(session->GetSquareManager()->FindSession(packet.uid)))
			session->Send(JoinResponseEvent{ square }.Compose(session));
		else
			return session->SendError<Opcode::SQUARE_JOIN_PARK_FAIL>(1403);
	}
};

#endif