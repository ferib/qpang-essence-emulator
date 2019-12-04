#ifndef LOBBY_NOTIFY_EVENT_HPP
#define LOBBY_NOTIFY_EVENT_HPP

#include <cstdint>

#include "packet_event.hpp"
#include "packet_data.hpp"
#include "auth_manager.hpp"
#include <boost/uuid/uuid.hpp>
#include "lobby_notify_response_event.hpp"

class LobbyNotifyEvent : public PacketEvent {

public:
	void Read(Connection::Ptr conn, ClientPacket& pack) override
	{
		auto lobbyNotify = pack.Read<Packets::Auth::LobbyNotify>();
		auto lobbyServer = AuthManager::Instance()->GetLobby();
		boost::uuids::uuid u;
		memcpy(&u, &lobbyNotify.uuid, 16);
		uint32_t userId = AuthManager::Instance()->ValidateSession(u);
		lobbyServer->SendPacket(LobbyNotifyResponseEvent{ userId, lobbyNotify.uuid }.Compose(conn));
	}
};

#endif