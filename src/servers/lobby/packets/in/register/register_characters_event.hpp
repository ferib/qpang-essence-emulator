#ifndef REGISTER_CHARACTERS_EVENT_HPP
#define REGISTER_CHARACTERS_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"
#include "database.hpp"
#include <boost/format.hpp>
#include <string>
#include "equipment_manager.hpp"
#include "register_characters_response_event.hpp"

class RegisterCharactersEvent : public LobbyPacketEvent {

public:
	RegisterCharactersEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::RegisterFinish)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::RegisterFinish>();
		std::string nickname = StringConverter::WcharToString(packet.requestName, 16);

		if (!session->Equipment()->ValidateCharacter(packet.character1) || !session->Equipment()->ValidateCharacter(packet.character2))
			return;

		if (session->GetLobby()->ValidateNickname(nickname))
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(820);

		Database database{};
		std::string query = str(boost::format("INSERT INTO players (user_id, name) VALUES (%1%, %2%)") % std::to_string(session->userId) % database.escapeString(nickname));
		database.executeQuery(query);

		uint32_t playerId = database.getLastInsertId();
		if (playerId == NULL)
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(836);

		query = "INSERT INTO player_equipment (player_id, character_id) VALUES ";
		for (size_t i = 0; i < EquipmentManager::Character::CHARACTER_COUNT; i++)
		{
			query += str(boost::format("(%1%, %2%),")
				% playerId % session->Equipment()->GetCharacterCode(i));
		}
		database.executeQuery(query.substr(0, query.size() - 1)); // getting rid of ','
		database.Close();

		session->Info()->Nickname(nickname);
		session->Send(RegisterCharactersResponseEvent{ nickname, packet.character1, packet.character2 }.Compose(session));
	};
};

#endif