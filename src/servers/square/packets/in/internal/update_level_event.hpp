#ifndef _UPDATE_LEVEL_EVENT_HPP
#define _UPDATE_LEVEL_EVENT_HPP

#include "packet_data.hpp"
#include <cstdint>
#include <vector>
#include <memory>
#include "square.hpp"
#include "square_packet_event.hpp"
#include "square_manager.hpp"
#include "login_response_event.hpp"
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"
#include "update_level_response_event.hpp"

class UpdateLevelEvent : public SquarePacketEvent {

public:
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		auto data = pack.Read<Packets::Internal::UpdatePlayerLevel>();

		auto targetSession = session->GetSquareManager()->FindSession(data.playerId);

		if(targetSession != nullptr)
		{
			auto square = targetSession->GetSquare();
			if(square != nullptr)
			{
				targetSession->Info()->SetLevel(data.level);
				square->SendPacket(UpdateLevelResponseEvent{ targetSession->Info()->Id(), targetSession->Info()->Rank() == 3 ? 46 : targetSession->Info()->Level() }.Compose(nullptr));
			}
		}
	}
};

#endif