#ifndef LOBBY_LOGIN_EVENT_HPP
#define LOBBY_LOGIN_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_notify_event.hpp"
#include "lobby.hpp"

class LobbyLoginEvent : public LobbyPacketEvent {

public:
	LobbyLoginEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::Login)){};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		
		auto lobbyLogin = pack.Read<Packets::Lobby::Login>();
		session->Info()->Uuid(lobbyLogin.uuid);
		auto authServer = session->GetLobby()->GetAuth();
		
		if(authServer)
			authServer->SendPacket(LobbyNotifyEvent{ lobbyLogin.uuid }.Compose(session));
	};
};

#endif