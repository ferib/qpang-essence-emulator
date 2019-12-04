#ifndef LOBBY_PACKET_HANDLER_HPP
#define LOBBY_PACKET_HANDLER_HPP

#include <map>
#include <memory>
#include <string>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "packet_handler.hpp"

//EVENTS
#include "handshake_event.hpp"
#include "lobby_packet_event.hpp"
#include "lobby_login_event.hpp"
#include "lobby_notify_response_event.hpp"
#include "lobby_channels_event.hpp"
#include "i_am_auth_event.hpp"
#include "i_am_square_event.hpp"
#include "channel_connect_event.hpp"
#include "register_nickname_event.hpp"
#include "register_characters_event.hpp"
#include "request_equipment_event.hpp"
#include "cash_event.hpp"
#include "cards_event.hpp"
#include "option_cards_event.hpp"
#include "memos_event.hpp"
#include "friends_event.hpp"
#include "ranking_event.hpp"
#include "equipped_skillcards_event.hpp"
#include "equip_armor_event.hpp"
#include "equip_weapon_event.hpp"
#include "character_event.hpp"
#include "drop_card_event.hpp"
#include "gift_card_event.hpp"
#include "open_gm_card_event.hpp"
#include "open_card_event.hpp"
#include "buy_card_event.hpp"
#include "gift_shop_card_event.hpp"
#include "player_info_event.hpp"
#include "add_friend_event.hpp"
#include "remove_outgoing_friend_event.hpp"
#include "accept_incoming_friend_event.hpp"
#include "deny_incoming_friend_event.hpp"
#include "remove_friend_event.hpp"
#include "send_memo_event.hpp"
#include "open_memo_event.hpp"
#include "remove_memo_event.hpp"
#include "crane_event.hpp"
#include "whisper_event.hpp"
#include "reload_crane_event.hpp"
#include "room_settings_event.hpp"
#include "i_am_room_event.hpp"
#include "reload_leaderboard.hpp"
#include "request_auth_event.hpp"
#include "update_gameroom_event.hpp"
//END EVENTS

#include "opcodes.hpp"
#include "package_goods_event.hpp"
#include "goods_event.hpp"
#include "gamerooms_event.hpp"
#include "room_random_invite_event.hpp"
#include "update_stats_event.hpp"
#include "request_player_equipment_event.hpp"

class LobbyPacketHandler : public PacketHandler {

public:
	LobbyPacketHandler()
	{
		sLogger->Get()->info("Loading lobby events");
		_events[Opcode::KEY_EXCHANGE] = new HandshakeEvent();
		_events[Opcode::LOBBY_LOGIN] = new LobbyLoginEvent();
		_events[Opcode::LOBBY_NOTIFY_RSP] = new LobbyNotifyResponseEvent();
		_events[Opcode::LOBBY_CHANNELS] = new ChannelsEvent();
		_events[Opcode::I_AM_AUTH] = new IAmAuthEvent();
		_events[Opcode::I_AM_SQUARE] = new IAmSquareEvent();
		_events[Opcode::LOBBY_CHANNEL_CONNECT] = new ChannelConnectEvent();
		_events[Opcode::LOBBY_REGISTER_NAME] = new RegisterNicknameEvent();
		_events[Opcode::LOBBY_REGISTER_CHARACTERS] = new RegisterCharactersEvent();
		_events[Opcode::LOBBY_INVENTORY_CARDS] = new CardsEvent();
		_events[Opcode::LOBBY_REQUEST_CASH] = new CashEvent();
		_events[Opcode::REQUEST_EQUIPMENT] = new RequestEqupmentEvent();
		_events[Opcode::LOBBY_GIFTS] = new GiftsEvent();
		_events[Opcode::LOBBY_MEMOS] = new MemosEvent();
		_events[Opcode::LOBBY_BUDDIES] = new FriendsEvent();
		_events[Opcode::LOBBY_PLAYER_RANKING] = new RankingEvent();
		_events[Opcode::LOBBY_EQUIPPED_SKILLS] = new EquippedSkillCardsEvent();
		_events[Opcode::LOBBY_EQUIP_ARMOUR] = new EquipArmorEvent();
		_events[Opcode::LOBBY_EQUIP_WEAPON] = new EquipWeaponEvent();
		_events[Opcode::LOBBY_SWAP_CHARACTER] = new CharacterEvent();
		_events[Opcode::LOBBY_DROP_CARD] = new DropCardEvent();
		_events[Opcode::LOBBY_GIFT_ITEM] = new GiftCardEvent();
		_events[Opcode::LOBBY_OPEN_GM_CARD] = new OpenGMCardEvent();
		_events[Opcode::LOBBY_OPEN_PLAYER_CARD] = new OpenCardEvent();
		_events[Opcode::LOBBY_BUY_ITEM] = new BuyCardEvent();
		_events[Opcode::LOBBY_SHOP_GIFT] = new GiftShopCardEvent();
		_events[Opcode::LOBBY_PLAYERINFO] = new PlayerInfoEvent();
		_events[Opcode::LOBBY_FRIEND_INVITE] = new AddFriendEvent();
		_events[Opcode::LOBBY_REMOVE_OUTGOING_FRIEND] = new RemoveOutgoingFriendEvent();
		_events[Opcode::LOBBY_ACCEPT_INCOMING_FRIEND] = new AcceptIncomingFriendEvent();
		_events[Opcode::LOBBY_DENY_INCOMING_FRIEND] = new DenyIncomingFriendEvent();
		_events[Opcode::LOBBY_REMOVE_FRIEND] = new RemoveFriendEvent();
		_events[Opcode::LOBBY_SEND_MEMO] = new SendMemoEvent();
		_events[Opcode::LOBBY_OPEN_MEMO] = new OpenMemoEvent();
		_events[Opcode::LOBBY_DELETE_MEMO] = new RemoveMemoEvent();
		_events[Opcode::LOBBY_USE_CRANE] = new CraneEvent();
		_events[Opcode::LOBBY_WHISPER] = new WhisperEvent();
		_events[Opcode::RELOAD_CRANE_COMMAND] = new ReloadCraneEvent();
		_events[Opcode::LOBBY_GAMESERVER_REFRESH] = new RoomSettingsEvent();
		_events[Opcode::I_AM_ROOM] = new IAmRoomEvent();
		_events[Opcode::RELOAD_LEADERBOARD_COMMAND] = new ReloadLeaderboardEvent();
		_events[Opcode::ROOM_REQUEST_AUTH] = new RequestAuthEvent();
		_events[Opcode::LOBBY_REQUEST_PACKAGE_GOODS] = new PackageGoodsEvent();
		_events[Opcode::LOBBY_REQUEST_GOODS] = new GoodsEvent();
		_events[Opcode::LOBBY_GAMEROOMS] = new GameroomsEvent();
		_events[Opcode::UPDATE_GAMEROOM] = new UpdateGameRoomEvent();
		_events[Opcode::LOBBY_RANDOM_INVITE] = new RoomRandomInviteEvent();
		_events[Opcode::LOBBY_ROOM_REQUEST_STATS] = new UpdateStatsEvent();
		_events[Opcode::ROOM_REQUEST_PLAYER_EQUIPMENT] = new RequestPlayerEquipmentEvent();
		sLogger->Get()->info("{0:d} events were loaded", _events.size());
	};

	void Execute(LobbySession* session, ClientPacket& pack)
	{
		if (_events.size() <= 0)
			return;

		if (session == nullptr)
			return;

		auto header = pack.ReadPayloadHeader();

		auto theEvent = _events.find(header.opcode);

		if (theEvent != _events.cend())
		{
			if (theEvent->second->size == 0 || header.length == theEvent->second->size)
			{
				try
				{
					sLogger->Get()->debug("{0} Packet {1:d}", session->Info()->Nickname(), static_cast<uint16_t>(header.opcode));
					return theEvent->second->Read(session, pack);
				}
				catch (std::exception & e)
				{
					sLogger->Get()->error("LobbyPacketHandler Error: {0}", e.what());
				}
			}
			
			uint16_t packetId = static_cast<uint16_t>(header.opcode);
			sLogger->Get()->error("Packet {0:d} should be of size: {1:d} actual on the server: {2:d}", packetId, header.length, theEvent->second->size);
		}

		sLogger->Get()->warn("Packet {0:d} is not being handled on the server yet", static_cast<uint16_t>(header.opcode));
	}
	// COMPLETE
private:
	std::map<Opcode, LobbyPacketEvent*> _events;
};

#endif