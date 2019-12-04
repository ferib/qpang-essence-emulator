#ifndef JOIN_BACK_EVENT_HPP
#define JOIN_BACK_EVENT_HPP

#include "square_packet_event.hpp"
#include "move_response_event.hpp"
#include "packet_data.hpp"
#include "join_back_response_event.hpp"
#include "change_player_state_event.hpp"
#include <array>

class JoinBackEvent : public SquarePacketEvent
{
	void Read(SquareSession* session, ClientPacket& pack) override 
	{
		std::array<float, 3> position = session->Info()->Position();
		session->Info()->SetState(ChangePlayerStateEvent::IDLE);

		sLogger->Get()->debug("Joinback event: {0} went back to the square", session->Info()->Nickname());

		auto square = session->GetSquare();
		if (square)
			square->SendPacket(ChangePlayerStateEvent{ session->Info()->Id(), ChangePlayerStateEvent::IDLE }.Compose(nullptr));
		else
			sLogger->Get()->warn("Joinbacke event: {0} wants to join back a square, but isn't in one", session->Info()->Nickname());

		session->Send(JoinBackResponseEvent{ position }.Compose(session));
	};
};


#endif // !UPDATE_PLAYER_EVENT_HPP
