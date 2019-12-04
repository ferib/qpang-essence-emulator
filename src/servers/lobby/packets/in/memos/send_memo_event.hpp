#ifndef SEND_MEMO_EVENT_HPP
#define SEND_MEMO_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"
#include "messenger_manager.hpp"
#include "lobby_session.hpp"
#include "lobby.hpp"
#include "message.hpp"
#include "send_memo_response_event.hpp"
#include "receive_memo_event.hpp"

class SendMemoEvent : public LobbyPacketEvent {

	enum Error {
		TARGET_CANNOT_RECEIVE_MEMO = 840,
		CANNOT_SEND_MEMO_MORE = 842,
		TARGET_NOT_ALLOW_MEMO = 843,
	};

public:
	SendMemoEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::SendMemo)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::SendMemo>();
		std::string targetNickname = StringConverter::WcharToString(packet.target, 16);
		std::string message = StringConverter::WcharToString(packet.message, 100);
		
		if (!session->GetLobby()->ValidateNickname(targetNickname))
			return session->SendError<Opcode::LOBBY_SEND_MEMO_FAIL>(Error::TARGET_CANNOT_RECEIVE_MEMO);

		auto target = session->GetLobby()->FindSession(targetNickname);

		if (target != nullptr)
		{
			Message memo = target->Messenger()->ReceiveMemo(session->Info()->Id(), target->Info()->Id(), session->Info()->Nickname(), message);

			if(memo.id == NULL)
				return session->SendError<Opcode::LOBBY_SEND_MEMO_FAIL>(Error::TARGET_CANNOT_RECEIVE_MEMO);

			target->Send(ReceiveMemoEvent{ memo }.Compose(session));
			session->Send(SendMemoResponseEvent{ 20 }.Compose(session));
		}
		else
		{
			//
		}
	}
};

#endif