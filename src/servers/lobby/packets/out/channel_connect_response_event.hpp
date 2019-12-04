#ifndef CHANNEL_CONNECT_RESPONSE_EVENT_HPP
#define CHANNEL_CONNECT_RESPONSE_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "channel.hpp"
#include "lobby.hpp"
#include "channel_manager.hpp"

class ChannelConnectResponseEvent : public LobbyPacketEvent {

public:
	ChannelConnectResponseEvent(Channel channel, uint32_t index) { _channel = channel; _index = index; };

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::ChannelConnectRsp rsp{};
		rsp.channelId = _index;
		rsp.channelServerIp = _channel.ipAddress;
		return ServerPacket::Create<Opcode::LOBBY_CHANNEL_CONNECT_RSP>(rsp);
	};
private:
	Channel _channel;
	uint32_t _index;
};

#endif