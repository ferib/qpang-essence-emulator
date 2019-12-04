#ifndef PLATER_JOIN_EVENT_HPP
#define PLAYER_JOIN_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include "square_session.hpp"
#include "player_join_response_event.hpp"
#include "add_player_event.hpp"
#include "square.hpp"
#include <vector>

//THIS IS THE EVENT WHICH IS GETTING CALLED WHEN A PLAYER JOINED A SQUARE
class PlayerJoinEvent : public SquarePacketEvent {

public:
	void Read(SquareSession* session, ClientPacket& pack) override
	{

		auto square = session->GetSquare();

		if (square != nullptr)
		{
			std::vector<std::shared_ptr<SquareSession>> players = square->List();

			sLogger->Get()->debug("Player join event: {0} is spawning in square {1:d}", session->Info()->Nickname(), square->Id());

			session->Send(PlayerJoinResponseEvent{ players }.Compose(session));
			square->SendPacket(AddPlayerEvent{}.Compose(session));
		}
		else
			sLogger->Get()->warn(("Player join event: {0} tried spawning in square, but isn't in one", session->Info()->Nickname()));
	}
};

#endif