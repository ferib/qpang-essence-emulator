#ifndef REGISTER_NICKNAME_EVENT_HPP
#define REGISTER_NICKNAME_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_notify_event.hpp"
#include "string_converter.hpp"
#include "packet_data.hpp"
#include "lobby.hpp"
#include "register_nickname_response_event.hpp"

class RegisterNicknameEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::CheckName>();
		std::string nickname = StringConverter::WcharToString(packet.requestName, 16);

		if (nickname.size() < 4 || nickname.size() > 16)
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(827);

		if (session->GetLobby()->ValidateNickname(nickname)) // nickname already exists
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(820);

		session->Send(RegisterNicknameResponseEvent{ nickname }.Compose(session));
	};
};

#endif