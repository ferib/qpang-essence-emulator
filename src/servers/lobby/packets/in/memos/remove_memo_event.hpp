#ifndef REMOVE_MEMO_EVENT_HPP
#define REMOVE_MEMO_EVENT_HPP

#include <cstdint>
#include <memory>
#include "packet_data.hpp"
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"
#include "messenger_manager.hpp"
#include "lobby_session.hpp"
#include "lobby.hpp"
#include "remove_memo_response_event.hpp"

class RemoveMemoEvent : public LobbyPacketEvent {

public:
	RemoveMemoEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::DeleteMemo)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::DeleteMemo>();

		if (session->Messenger()->RemoveMemo(static_cast<uint32_t>(packet.memoId)))
			session->Send(RemoveMemoResponseEvent{ packet.memoId }.Compose(session));
	}
};

#endif