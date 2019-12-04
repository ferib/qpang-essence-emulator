#ifndef LOBBY_NOTIFY_RESPONSE_EVENT_HPP
#define LOBBY_NOTIFY_RESPONSE_EVENT_HPP

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "lobby_login_response_event.hpp"

class LobbyNotifyResponseEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* authSession, ClientPacket& pack) override
	{
		auto notifyResponse = pack.Read<Packets::Auth::LobbyNotifyRsp>();
		uint32_t userId = notifyResponse.userId;

		auto gameSession = authSession->GetLobby()->FindSession(notifyResponse.uuid);

		if (gameSession == nullptr)
			return;

		sLogger->Get()->debug("Lobby Notify RSP: valid: {0:d}", notifyResponse.valid);

		if (!notifyResponse.valid)
		{
			gameSession->SendError<Opcode::LOBBY_SERVER_ERROR>(803);
			return gameSession->Disconnect();
		}

		gameSession->Send(LoginResponseEvent{userId}.Compose(gameSession.get()));
	};
};

#endif