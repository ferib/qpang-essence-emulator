#ifndef LOGIN_RESPONSE_EVENT_HPP
#define LOGIN_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <memory>
#include <vector>
#include <cstdint>
#include "string_converter.hpp"

class LoginResponseEvent : public SquarePacketEvent {

public:
	LoginResponseEvent(std::vector<Square::Ptr> squares) { _squares = squares; };

	ServerPacket Compose(SquareSession* session) override {
		Packets::Square::LoginRsp rsp{};
		
		uint32_t size = _squares.size();
		rsp.totalCount = size;
		rsp.countInPacket = size;
		rsp.unknown = size;

		for (size_t i = 0; i < size; i++)
		{
			Packets::Square::LoginRsp::Park park = rsp.park[i];
			Square::Ptr square = _squares.at(i);

			park.id = square->Id();
			park.state = square->State();
			park.currPlayers = square->List().size();
			park.maxPlayers = square->MaxCapacity();
			wcscpy(park.name, StringConverter::StringToWChar(square->Name()));
			//wcsncpy(park.name, std::wstring(square->Name().begin(), square->Name().end()).data());

			rsp.park[i] = park;
		}

		return ServerPacket::Create<Opcode::SQUARE_LOGIN_RSP>(rsp);
	};
private:
	std::vector<Square::Ptr> _squares;
};

#endif