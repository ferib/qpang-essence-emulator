#ifndef GAMEROOMS_RESPONSE_EVENT_HPP
#define GAMEROOMS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "gameroom.hpp"
#include "settings_manager.hpp"

class GameroomsResponseEvent : public LobbyPacketEvent {

public:	
	GameroomsResponseEvent(std::vector<GameRoom> rooms) { _rooms = rooms; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::GameRoomList rsp{};

		rsp.countInPacket = _rooms.size();
		rsp.totalCount = _rooms.size();
		rsp.unknown = _rooms.size();

		for (size_t i = 0; i < _rooms.size(); i++)
		{
			auto& gameroom = _rooms.at(i);

			rsp.rooms[i].roomId = gameroom.id;
			wcsncpy(rsp.rooms[i].roomName, std::wstring(gameroom.name.begin(), gameroom.name.end()).data(), 30);
			rsp.rooms[i].host = inet_addr(sSettings->GetSetting("room_host").c_str());
			rsp.rooms[i].port = boost::lexical_cast<uint16_t>(sSettings->GetSetting("room_port"));
			rsp.rooms[i].currplayers = gameroom.currPlayers;
			rsp.rooms[i].passwordProtected = 8;
			rsp.rooms[i].maxPlayers = gameroom.maxPlayers;
			rsp.rooms[i].mapId = gameroom.map;
			rsp.rooms[i].modeId = gameroom.mode;
			rsp.rooms[i].state = gameroom.state;
			rsp.rooms[i].meleeOnly = gameroom.meleeOnly;
		}

		return ServerPacket::Create<Opcode::LOBBY_GAMEROOMS_RSP>(rsp);
	};
private:
	std::vector<GameRoom> _rooms;
};

#endif