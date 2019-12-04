#ifndef MEMOS_EVENT_HPP
#define MEMOS_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include <vector>
#include "memos_response_event.hpp"
#include "message.hpp"
#include "lobby_session.hpp"
#include "messenger_manager.hpp"

class MemosEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::vector<Message> messages = session->Messenger()->List();
		session->Send(MemosResponseEvent{ messages }.Compose(session));
	}
};

#endif