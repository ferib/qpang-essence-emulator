#ifndef ADD_PLAYER_EVENT_HPP
#define ADD_PLAYER_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <array>
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class AddPlayerEvent : public SquarePacketEvent {

public:
	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkAddPlayer rsp{};
		rsp.id = session->Info()->Id();
		rsp.level = session->Info()->Level();
		rsp.rank = session->Info()->Rank();
		rsp.characterId = session->Info()->Character();
		std::array<uint32_t, 9> allEquipment = session->Info()->Equipment();
		rsp.state = 0;
		rsp.equipment = allEquipment;
		rsp.position = session->Info()->Position();
		wcsncpy(rsp.name, StringConverter::StringToWString(session->Info()->Nickname()).data(), 16);
		return ServerPacket::Create<Opcode::SQUARE_ADD_PLAYER>(rsp);
	}
private:
};

#endif