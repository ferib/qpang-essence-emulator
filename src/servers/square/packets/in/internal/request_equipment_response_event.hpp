#ifndef REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP
#define REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP

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

class RequestEquipmentResponseEvent : public SquarePacketEvent {

public:
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Internal::RequestEquipmentRsp>();
		if (packet.status)
		{
			auto targetSession = session->GetSquareManager()->FindSession(packet.playerId);
			std::vector<Square::Ptr> squares = session->GetSquareManager()->List();
			if (targetSession != nullptr)
			{
				targetSession->Info()->SetId(packet.playerId);
				targetSession->Info()->SetCharacter(packet.character);
				targetSession->Info()->SetEquipment(packet.equipment);
				targetSession->Info()->SetRank(packet.rank);
				targetSession->Info()->SetLevel(packet.level);
				targetSession->Info()->SetPrestige(packet.prestige);
				targetSession->Info()->SetNickname(StringConverter::WcharToString(packet.nickname, 16));

				sLogger->Get()->debug("Sending Login Event to {0} ", targetSession->Info()->Nickname());
				targetSession->Send(LoginResponseEvent{ squares }.Compose(targetSession.get()));
			}
		}
		else
			sLogger->Get()->debug("{0:d} failed to login, status: {1:d}", packet.playerId, packet.status);
	}
};

#endif