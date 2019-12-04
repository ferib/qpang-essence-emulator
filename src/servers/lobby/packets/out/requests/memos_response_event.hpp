#ifndef MEMOS_RESPONSE_EVENT_HPP
#define MEMOS_RESPONSE_EVENT_HPP

#include <memory>

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "message.hpp"
#include "string_converter.hpp"
#include "messenger_manager.hpp"

class MemosResponseEvent : public LobbyPacketEvent {

public:
	MemosResponseEvent(std::vector<Message> messages) { _messages = messages; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::MemosRequestRsp rsp{};
		rsp.totalCount = _messages.size();
		rsp.unknown = _messages.size();
		rsp.countInPacket = _messages.size();

		for (int32_t i = 0; i < _messages.size(); i++)
		{
			if (i >= MAX_MESSAGES)
				break;

			int32_t placeHolderI = i;
			Packets::Lobby::Memo memo = rsp.memos[i];
			Message message = _messages.at(i);
			memo.senderId = message.senderId;
			memo.date = message.received;
			memo.opened = message.opened;
			memo.id = message.id;
			wcsncpy(memo.sender, std::wstring(message.senderName.begin(), message.senderName.end()).data(), 16);
			wcsncpy(memo.body, std::wstring(message.messageBody.begin(), message.messageBody.end()).data(), 100);
			rsp.memos[placeHolderI] = memo;
		}

		return ServerPacket::Create<Opcode::LOBBY_MEMOS_RSP>(rsp);
	};
private:
	std::vector<Message> _messages;
};

#endif