#ifndef CHANNEL_CONNECT_EVENT_HPP
#define CHANNEL_CONNECT_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "lobby.hpp"
#include "lobby_session.hpp"
#include "channel_connect_response_event.hpp"
#include "friend_manager.hpp"
#include "set_online_event.hpp"

class ChannelConnectEvent : public LobbyPacketEvent {

public:
	ChannelConnectEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::ChannelConnect)) {};

	void Read(LobbySession* session, ClientPacket& pack) override
	{
		auto packet = pack.Read<Packets::Lobby::ChannelConnect>();

		if (session->GetLobby()->Channels()->GetChannel(session->Info()->Channel()) != nullptr)
			session->GetLobby()->Channels()->RemovePopulation(session->Info()->Channel());

		Channel channel = *(session->GetLobby()->Channels()->GetChannel(packet.channelId));
		if (!session->GetLobby()->Channels()->AddPopulation(packet.channelId) || packet.channelId == NULL)
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(852);

		session->Info()->Channel(packet.channelId);

		auto onlineEvent = SetOnlineEvent{ session->Info()->Id() }.Compose(session);
		session->Friends()->SendPacket(onlineEvent, session->GetLobby());
		session->Send(ChannelConnectResponseEvent{ channel, packet.channelId }.Compose(session));
	};
};

#endif