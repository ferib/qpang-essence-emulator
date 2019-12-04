#ifndef UPDATE_PLAYER_EVENT_HPP
#define UPDATE_PLAYER_EVENT_HPP

#include "square_packet_event.hpp"
#include "move_response_event.hpp"
#include "packet_data.hpp"
#include <array>
#include <cstdint>
#include "update_player_response_event.hpp"

class UpdatePlayerEvent : public SquarePacketEvent
{
public:
	UpdatePlayerEvent() : SquarePacketEvent(sizeof(Packets::Square::ParkPlayerUpdate)) {};
	void Read(SquareSession* session, ClientPacket& pack) override 
	{
		auto packet = pack.Read<Packets::Square::ParkPlayerUpdate>();
		auto square = session->GetSquare();

		if (square)
		{
			sLogger->Get()->debug("{0} left the inventory, updating player look", session->Info()->Nickname());
			std::array<uint32_t, 9> equipment = session->Info()->Equipment();
			for (size_t i = 0; i < equipment.size(); i++)
			{
				equipment[i] = packet.equipment[i];
			}

			session->Info()->SetEquipment(equipment);
			session->Info()->SetCharacter(packet.characterId);
			square->SendPacket(UpdatePlayerResponseEvent{ session->Info()->Id(), packet.characterId, session->Info()->Equipment() }.Compose(session));
		}
		else
			sLogger->Get()->warn("{0} left the inventory, but is not in a square", session->Info()->Nickname());
	};
};


#endif // !UPDATE_PLAYER_EVENT_HPP
