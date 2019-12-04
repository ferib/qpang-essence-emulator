#ifndef PLAYER_JOIN_RESPONSE_EVENT_HPP
#define PLAYER_JOIN_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square.hpp"
#include <memory>
#include <vector>
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class PlayerJoinResponseEvent : public SquarePacketEvent {

public:
	PlayerJoinResponseEvent(std::vector<std::shared_ptr<SquareSession>> sessions) { _sessions = sessions; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkLoadPlayers rsp{};
		uint32_t size = _sessions.size();
		rsp.countInPacket = size;
		rsp.totalCount = size;
		rsp.unknown = size;

		for (size_t i = 0; i < size; i++)
		{
			Packets::Square::ParkLoadPlayers::SquarePlayer player = rsp.squarePlayer[i];
			SquareSession::Ptr otherSession = _sessions.at(i);

			if (session->Info()->Id() != otherSession->Info()->Id())
			{
				player.id = otherSession->Info()->Id();
				player.level = otherSession->Info()->Level();
				player.character = otherSession->Info()->Character();
				player.rank = otherSession->Info()->Rank();
				wcsncpy(player.nickname, StringConverter::StringToWString(otherSession->Info()->Nickname()).data(), 16);
				player.state = otherSession->Info()->State();
				player.refers = otherSession->Info()->Prestige();
				for (size_t i = 0; i < 3; i++)
				{
					player.position[i] = otherSession->Info()->Position()[i];
				}
				player.equipment = otherSession->Info()->Equipment();
				rsp.squarePlayer[i] = player;
			}
		}

		return ServerPacket::Create<Opcode::SQUARE_LOAD_PLAYERS>(rsp);
	}
private:
	std::vector<std::shared_ptr<SquareSession>> _sessions;
};

#endif