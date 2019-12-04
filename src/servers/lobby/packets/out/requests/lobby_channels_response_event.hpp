#ifndef CHANNELS_RESPONSE_EVENT_HPP
#define CHANNELS_RESPONSE_EVENT_HPP

#include <memory>
#include <vector>
#include "channel.hpp"
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"

class ChannelsResponseEvent : public LobbyPacketEvent {

public:
	ChannelsResponseEvent(std::vector<Channel> channels) { _channels = channels; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::ChannelsRsp rsp{};
		
		uint16_t size = _channels.size();
		rsp.countInPacket = size;
		rsp.totalCount = size;
		rsp.unknown = size;

		for (size_t i = 0; i < size; i++)
		{
			Channel channel = _channels[i];
			if (channel.minRank > session->Info()->Rank())
				continue;

			rsp.channels[i].index = i + 1; // 0 = no channel, if we put index to 0 'already in channel'
			wcsncpy(rsp.channels[i].name, std::wstring(channel.name.begin(), channel.name.end()).data(), 30);
			rsp.channels[i].minLevel = channel.minLevel;
			rsp.channels[i].maxLevel = channel.maxLevel;
			rsp.channels[i].currPlayers = channel.currPlayers;
			rsp.channels[i].maxPlayers = channel.maxPlayers;
			rsp.channels[i].minLevel = channel.minLevel;
		}

		return ServerPacket::Create<Opcode::LOBBY_CHANNELS_RSP>(rsp);
	};
private:
	std::vector<Channel> _channels;

};

#endif