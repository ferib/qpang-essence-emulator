#ifndef OPEN_MEMO_EVENT_HPP
#define OPEN_MEMO_EVENT_HPP

#include <cstdint>
#include <memory>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"
#include "messenger_manager.hpp"
#include "lobby_session.hpp"
#include "lobby.hpp"
#include "message.hpp"

#include "open_memo_response_event.hpp"

class OpenMemoEvent : public LobbyPacketEvent {

public:
	OpenMemoEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::ReadMemo)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::ReadMemo>();

		session->Messenger()->OpenMemo(packet.memoId);
		session->Send(OpenMemoResponseEvent{ static_cast<uint32_t>(packet.memoId) }.Compose(session));
	}
};

#endif