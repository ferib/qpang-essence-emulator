#ifndef LOBBY_CHANNELS_EVENT_HPP
#define LOBBY_CHANNELS_EVENT_HPP

#include <memory>
#include <vector>
#include "channel.hpp"
#include "lobby_channels_response_event.hpp"

class ChannelsEvent : public LobbyPacketEvent {
public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::vector<Channel> channels = session->GetLobby()->Channels()->List();
		session->Send(ChannelsResponseEvent{channels}.Compose(session));
	}
};

#endif