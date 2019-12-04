#ifndef MOVE_EVENT_HPP
#define MOVE_EVENT_HPP

#include "square_packet_event.hpp"
#include "move_response_event.hpp"
#include "packet_data.hpp"

class MoveEvent : public SquarePacketEvent
{
public:
	MoveEvent() : SquarePacketEvent(22) {};
	void Read(SquareSession* session, ClientPacket& pack) override 
	{
		auto packet = pack.Read<Packets::Square::ParkPlayerMove>();

		sLogger->Get()->trace("{0} moved to location: {1:f}, {2:f}, {3:f}", session->Info()->Nickname(), packet.position[0], packet.position[1], packet.position[2]);

		auto square = session->GetSquare();
		if (square)
		{
			session->Info()->SetPosition(packet.position);
			square->SendPacket(MoveResponseEvent{ session->Info()->Id(), packet.position, packet.type, packet.direction }.Compose(session));
		}
	};
};


#endif // !MOVE_EVENT_HPP
