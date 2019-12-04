#ifndef RECEIVE_MEMO_EVENT_HPP
#define RECEIVE_MEMO_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "message.hpp"
#include "string_converter.hpp"

class ReceiveMemoEvent : public LobbyPacketEvent {

public:
	ReceiveMemoEvent(Message message) { _message = message; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::ReceiveMemo rsp{};
		rsp.memo.id = _message.id;
		rsp.memo.date = _message.received;
		wcsncpy(rsp.memo.sender, std::wstring(_message.senderName.begin(), _message.senderName.end()).data(), 16);
		wcsncpy(rsp.memo.body, std::wstring(_message.messageBody.begin(), _message.messageBody.end()).data(), 98);
		rsp.memo.senderId = _message.senderId;
		rsp.memo.opened = false;
		return ServerPacket::Create<Opcode::LOBBY_RECEIVE_MEMO>(rsp);
	};
private:
	Message _message;
};

#endif