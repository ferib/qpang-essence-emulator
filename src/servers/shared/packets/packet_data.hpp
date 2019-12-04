#ifndef _PACKET_DATA_H
#define _PACKET_DATA_H

#include <cstdint>
#include <array>

namespace Packets
{
	struct PacketData
	{
		//opaque...
	};

	struct ClientPacketData
	{
		uint32_t id;
	};

	struct ServerPacketData
	{
		uint32_t unknown; //could be id as well

		template<typename T, size_t N>
		void WriteToArray(const std::vector<T>& src, T (&dest)[N])
		{
			std::copy(std::begin(src), std::end(src), std::begin(dest));
		}
	};

	struct Error : ServerPacketData
	{
		uint32_t errorId;
	};

	namespace Handshake
	{
		struct KeyExchange : ClientPacketData
		{
			uint32_t unknown;
		};


		struct KeyExchangeRsp : ServerPacketData
		{
			char keyPart[4];
		};
	}

	namespace Auth
	{

		struct Login : ClientPacketData
		{
			char padding[16]; //8
			wchar_t loginId[21]; //24
			wchar_t password[17]; //66
			uint32_t unk;
			uint32_t unk_01;
			uint32_t unknown; //104
			uint32_t gameVersion; //108
			uint32_t unk_02;
		};

		struct LoginRsp : ServerPacketData
		{
			uint32_t lobbyServerIp; 
			std::array<uint8_t, 16> uuid;
		};

		struct LobbyNotifyRsp : ClientPacketData
		{
			uint32_t userId;
			bool valid;
			std::array<uint8_t, 16> uuid;
		};

		struct LobbyNotify : ServerPacketData
		{
			std::array<uint8_t, 16> uuid;
		};
	}

	namespace Lobby
	{
		struct Login : ClientPacketData
		{
			std::array<uint8_t, 16> uuid;
			char unk[56];
		};

		
		struct LoginRsp : ServerPacketData
		{
#pragma pack(push, 1)
			struct CharacterEquipment
			{
				struct PartItem
				{
					uint64_t cardId;
				};

				struct WeaponItem
				{
					uint64_t cardId;
					uint64_t unknown;
				};

				uint16_t characterId;
				PartItem hair;
				PartItem face;
				PartItem body;
				PartItem hands;
				PartItem pants;
				PartItem shoes;
				PartItem back;
				PartItem side;
				PartItem unkPart;
				WeaponItem primaryWeapon;//WeaponItem meleeWeapon;
				WeaponItem secondaryWeapon;//WeaponItem primaryWeapon;
				WeaponItem throwWeapon;
				WeaponItem meleeWeapon;
			};
#pragma pack(pop)

#pragma pack(push, 1)
			struct Title
			{
				uint32_t id;
				uint32_t unknown;
			};

			uint32_t uid; //8
			char pad01[42]; //12
			wchar_t nickname[17]; //54
			uint32_t playTime;
			uint32_t cash; //92
			uint32_t rank; //96
			uint16_t unknown01; //100
			uint16_t defaultCharacter; //102
			uint32_t level; //104
			char pad02[8]; //108
			bool acceptPm; //116
			bool acceptInvites; //117
			bool acceptFriendRequests; //118
			bool unknown02; //119
			bool acceptTradeRequests; //120
			char pad03[20]; //121
			uint8_t completedTutorialChallenges; //141
			char pad04[12]; //142
			uint16_t inventoryCapacity; //147
			uint16_t friendListCapacity; //149
			uint16_t friendListOutgoingCapacity; //151
			uint16_t memoListDailyCapacity; //153
			uint16_t memosLeft; //155
			uint32_t unknown03; //157
			uint32_t experience; //151
			uint32_t don; //155
			uint32_t unknown04; //159
			uint32_t kills;
			uint32_t deaths;
			uint32_t wonAsTeam;
			uint32_t lostAsTeam;
			uint32_t drawnAsTeam;
			uint32_t unknown05;
			uint32_t missionsWon;
			uint32_t missionsLost;
			uint32_t missionsDrawn;
			char pad05[72];
			uint32_t slackerPoints;
			uint32_t coins;
			char pad06[44];
			CharacterEquipment equipment[6]; //size: 828
			char pad07[1075 - (sizeof(CharacterEquipment) * 4)];
			uint16_t unlockedTitleCount;
			Title titles[30]; //probably way more than that
			char pad08[785];
			uint32_t unknown06;
#pragma pack(pop)
		};

		struct ChannelsRsp : ServerPacketData
		{
			struct Channel
			{
				uint16_t index; 
				wchar_t name[31]; 
				uint8_t minLevel; 
				uint8_t maxLevel; 
				uint16_t currPlayers; 
				uint16_t maxPlayers; 
				char pad[51];
			};

			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			Channel channels[10];
		};

		struct ChannelConnect : ClientPacketData
		{
			uint32_t channelId;
			uint32_t unknown01;
			uint32_t unknown02;
			uint32_t unknown03;
			uint32_t unknown04;
			uint32_t unknown05;
		};
#pragma pack(push, 1)
		struct ChannelConnectRsp : ServerPacketData
		{
			uint32_t channelId;
			uint64_t unknown03;
			uint32_t channelServerIp;
			uint32_t unknown05;
			uint32_t unknown06;
			uint32_t unknown07;
		};

#pragma pack(push, 1)
		struct InventoryCardsRsp : ServerPacketData
		{

			//will be moved out of the struct later...
			struct Card
			{
				uint64_t cardId;
				uint32_t itemId;
				uint8_t unknown01;
				uint8_t type; //87: weapons, 86: armor, 73: skills
				uint8_t unknown02;
				bool giftable;
				char padding[6];
				uint32_t dateReceived;
				bool opened; //set to 1??
				uint16_t unknown03;
				bool hidden;
				uint8_t unknown04; //set to 2
				uint16_t period;
				uint8_t periodType; //set to 3
				uint8_t unknown05; //set to 1
				uint16_t boostLevel;
				bool isBoosted;
				uint8_t unknown06;
				char padding2[4];
			};

			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			Card cards[200]; //for now
		};

		struct GiftsRsp : ServerPacketData
		{
			struct GiftCard {
				wchar_t nickname[17];
				uint32_t cardId;
				uint32_t unk_01;
				bool unk_02;
				uint64_t dateReceived;
			};

			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			GiftCard cards[20];
		};

		struct CheckName : ClientPacketData 
		{
			wchar_t requestName[17];
		};

		struct CheckNameRsp : ServerPacketData 
		{
			wchar_t responseName[17];
		};

		struct RegisterFinish : ClientPacketData 
		{
			wchar_t requestName[17];
			wchar_t referrerName[17];
			uint16_t character1;
			uint16_t character2;
			uint32_t unk_01;
		};

		struct RegisterFinishRsp : ServerPacketData 
		{
			wchar_t responseName[17];
			uint16_t defaultCharacter;
			uint16_t character1;
			char unk01[136];
			uint16_t character2;
			char unk02[136];
		};

		struct TutorialPartFinish : ClientPacketData
		{
			uint8_t part;
		};

		struct TutorialPartFinishRsp : ServerPacketData
		{
			uint8_t part;
			uint8_t unk01;
			uint32_t don;
			uint32_t title;

			// copied from another packet
			uint16_t totalCount;
			uint16_t unknown;
			uint8_t countInPacket;
			InventoryCardsRsp::Card cards[6]; // for now
		};

		struct GameRefreshRsp : ServerPacketData
		{
			bool canCreateRooms;
			uint32_t gameServerIp;
			uint16_t gameServerPort;
			char padding[42];
		};

		struct CashRequestRsp : ServerPacketData
		{
			uint32_t amount;
		};

		struct PlayerRankingRsp : ServerPacketData
		{
			uint32_t something;
			uint32_t rank;
			uint32_t amount;
		};

		struct EquippedSkillCardsRsp : ServerPacketData
		{
			InventoryCardsRsp::Card card[3];
			char pad01[954];
		};

		struct RemoveOutgoingFriend : ClientPacketData
		{
			uint32_t targetId;
			char unk[46];
		};

		struct RemoveOutgoingFriendRsp : ServerPacketData
		{
			uint32_t targetId;
		};

		struct BuddiesRequestRsp : ServerPacketData
		{
			struct Buddy
			{
				uint32_t id;
				char pad01[4];
				uint8_t friendState;
				bool isOnline;
				uint16_t level;
				wchar_t name[17];
			};

			/* The amount of entries that were sent to far, INCLUDING THE AMOUNT IT WILL SEND IN THIS NEXT PACKET */
			uint16_t totalSent;
			/* The amount of entries there are in total */
			uint16_t totalCount;
			/* The amount of entries sent in this packet */
			uint16_t countInPacket;

			Buddy buddies[20];

		};

		struct AddIncomingFriend : ServerPacketData
		{
			BuddiesRequestRsp::Buddy buddy;
		};


		struct Memo
		{
			uint64_t id;
			uint32_t senderId;
			uint32_t date;
			wchar_t sender[17];
			wchar_t body[101];
			bool opened;
		};

		struct MemosRequestRsp : ServerPacketData
		{
			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			Memo memos[19];
		};


#pragma pack(pop)
#pragma pack(pop)
#pragma pack(push, 1)
		struct CharacterChange : ClientPacketData
		{
			uint16_t characterId;
			uint32_t unk_01;
		};
		struct CharacterChangeRsp : ServerPacketData
		{
			uint16_t characterId;
		};
		struct EquipWeapon : ClientPacketData
		{
			uint16_t characterOffset;
			uint64_t primary_card;
			uint64_t unknown1;
			uint64_t secondary_card;
			uint64_t unknown2;
			uint64_t throw_card;
			uint64_t unknown3;
			uint64_t melee_card;
			uint64_t unknown4;
			uint32_t unk_01;
		};

		struct EquipWeaponRsp : ServerPacketData
		{
			uint16_t characterOffset;
			uint64_t primary_card;
			uint64_t unknown1;
			uint64_t secondary_card;
			uint64_t unknown2;
			uint64_t throw_card;
			uint64_t unknown3;
			uint64_t melee_card;
			uint64_t unknown4;
		};
		struct EquipArmour : ClientPacketData
		{
			uint16_t characterOffset;
			uint64_t head;
			uint64_t face;
			uint64_t body;
			uint64_t hands;
			uint64_t pants;
			uint64_t shoes;
			uint64_t back;
			uint64_t side;
			uint64_t unk_part;
			uint32_t unk_01;
		};
		struct EquipArmourRsp : ServerPacketData
		{
			uint16_t characterOffset;
			uint64_t head;
			uint64_t face;
			uint64_t body;
			uint64_t hands;
			uint64_t pants;
			uint64_t shoes;
			uint64_t back;
			uint64_t side;
		};

		struct UpdatePlayerStats : ServerPacketData
		{
			uint32_t unk_00;
			uint32_t experience;
			uint32_t don;
			uint32_t unk_01;
			uint32_t kills;
			uint32_t deaths;
			uint32_t tdm_wins;
			uint32_t tdm_losses;
			uint32_t tdm_ties;
			uint32_t unk_02;
			uint32_t mission_wins;
			uint32_t mission_losses;
			uint32_t mission_ties;
			uint32_t unk_03;
			uint32_t unk_04;
			uint32_t unk_05;
			uint32_t unk_06;
			uint32_t unk_07;
			uint32_t unk_08;
			uint32_t unk_09;
			uint32_t unk_10;
			uint32_t unk_11;
			uint32_t unk_12;
			uint32_t unk_13;
			uint32_t unk_14;
			uint32_t unk_15;
			uint32_t unk_16;
			uint32_t unk_17;
			uint32_t unk_18;
			uint32_t unk_19;
			uint32_t unk_20;
			uint32_t slackerPoints;
			uint32_t coins;
		};

		struct RequestPlayerInfo : ClientPacketData
		{
			uint32_t targetId;
			char unk[38];
		};

		struct RequestPlayerInfoRsp : ServerPacketData
		{

			struct Character {
				struct Weapon {
					uint32_t itemId;
					uint32_t unk_01;
				};

				uint16_t characterId;
				uint32_t head;
				uint32_t face;
				uint32_t body;
				uint32_t hands;
				uint32_t pants;
				uint32_t boots;
				uint32_t back;
				uint32_t side;
				char unk_01[4];
				Weapon primaryWeapon;
				Weapon secondaryWeapon;
				Weapon throwWeapon;
				Weapon meleeWeapon;
			};

			uint32_t userId;
			char unk_02[42];
			wchar_t nickname[17];
			uint32_t playTime;
			char unk_03[4];
			uint8_t level;
			uint8_t rank;
			Character character;
			char unk_04[40];
			uint32_t exp;
			char unk_05_[4];
			uint32_t unk_05;
			uint32_t unk_06;
			uint32_t unk_07;
			uint32_t unk_08;
			char unk_09[4];
			uint32_t unk_10;
			uint32_t unk_11;
			uint32_t unk_12;
			char unk_13[4];
			uint16_t slackerPoints;
			char unk_14[4];
			uint32_t leaderboardRank;
			uint32_t leaderboardGained;
			LoginRsp::Title titles[40];
		};

		struct GameRoomList : ServerPacketData
		{
			struct GameRoom
			{
				uint32_t host;
				uint16_t port;
				uint32_t roomId;
				char pad01[2]; 
				wchar_t roomName[31];
				char pad02[14];
				uint8_t mapId; 
				uint8_t modeId; 
				uint8_t passwordProtected; 
				uint8_t state;
				uint8_t currplayers; 
				uint8_t maxPlayers;
				char pad04[5];
				bool levelLimit;
				bool teamSorting;
				bool enableSkill;
				char pad05[2];
				bool meleeOnly;
			};
			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			GameRoom rooms[50];
		};

		struct GiftShopCard : ClientPacketData
		{
			wchar_t nickname[17];
			char pad01[4];
			uint32_t goodId;
			char unk[18];
		};

		struct GiftShopCardRsp : ServerPacketData
		{
			wchar_t nickname[17];
			uint32_t moneyLeft;
			char pad01[8];
			uint8_t currencyType;
		};

		struct GiftCard : ClientPacketData
		{
			wchar_t nickname[17];
			uint64_t cardId;
			uint32_t unk_01;
		};

		struct GiftCardRsp : ServerPacketData
		{
			char pad01[34];
			uint64_t cardId;
		};

		struct ReceiveGift : ServerPacketData
		{
			wchar_t nickname[17];
			uint32_t cardId;
			uint32_t unk_01;
			uint8_t unk_02;
			uint64_t dateReceived;
		};

		struct UseCrane : ClientPacketData
		{
			uint16_t times;
			uint32_t unk_01;
		};
		
		struct UseCraneRsp : ServerPacketData
		{
			struct Reward {
				uint32_t itemId;
				char unk_01[5];
				InventoryCardsRsp::Card card;
			};

			uint16_t times;
			uint32_t newDon;
			uint32_t newCoins;
			Reward rewards[7];
		};

		struct ToggleFriendStatus : ServerPacketData
		{
			uint32_t targetId;
		};

		struct FriendRequest : ClientPacketData
		{
			char unk_01[12];
			wchar_t username[17];
			uint32_t unk_02;
		};

		struct AcceptFriendRequest : ClientPacketData
		{
			uint32_t newFriendId;
			char unk[46];
		};

		struct DenyFriendRequest : ClientPacketData
		{
			uint32_t playerId;
			char unk[46];
		};

		struct Friend
		{
			uint32_t friendId;
			uint16_t unk_02;
			uint16_t unk_03;
			uint8_t friendState;
			bool isOnline;
			uint16_t friendLevel;
			wchar_t friendName[17];
		};

		struct AcceptFriendRequestRsp : ServerPacketData
		{
			Packets::Lobby::Friend newFriend;
		};

		
		struct DenyFriendRequestRsp : ServerPacketData
		{
			uint32_t deniedFriendId;
		};

		struct DenyFriendRequestTargetRsp : ServerPacketData
		{
			uint32_t pendingFriendId;
			char unk_01[8];
			wchar_t nickname[17];
		};

		struct RemoveFriend : ClientPacketData
		{ 
			uint32_t removedFriendId;
			char unk[46];
		};

		struct RemoveIncomingFriend : ServerPacketData
		{
			uint32_t playerId;
			char pad[8];
			wchar_t nickname[17];
		};

		struct RemoveFriendRsp : ServerPacketData
		{
			uint32_t removedFriendId;
			char unk[46];
		};

		struct FriendRsp : ServerPacketData
		{
			Packets::Lobby::Friend newFriend;
		};

		struct NotifyFriendStatus : ServerPacketData
		{
			uint32_t friendId;
			char unk_01[40];
		};

		struct SendMemo : ClientPacketData
		{
			uint32_t targetId;
			wchar_t target[17];
			wchar_t message[101];
			uint32_t unk_01;
		};

		struct ReceiveMemo : ServerPacketData
		{
			Memo memo;
		};

		struct SendMemoRsp : ServerPacketData
		{
			uint32_t memosLeft;
		};

		struct SendMemoTargetRsp : ServerPacketData
		{
			Memo memo;
		};

		struct ReadMemo : ClientPacketData
		{
			uint64_t memoId;
			uint32_t unk_01;
		};

		struct ReadMemoRsp : ServerPacketData
		{
			uint64_t memoId;
		};

		struct DeleteMemo : ClientPacketData
		{
			uint64_t memoId;
			uint32_t unk;
		};

		struct DeleteMemoRsp : ServerPacketData
		{
			uint64_t memoId;
		};

		struct DeleteCard : ClientPacketData
		{
			uint64_t cardId;
			uint32_t unk;
		};

		struct DeleteCardRsp : ServerPacketData
		{
			uint64_t cardId;
		};

		struct OpenCard : ClientPacketData
		{
			uint32_t cardId;
			uint32_t unk;
			char unk_02[4];
		};

		struct OpenOnlineCard : ClientPacketData
		{
			uint32_t cardId;
			uint32_t unk;
			char unk_02[8];
		};

		struct OpenCardRsp : ServerPacketData 
		{
			InventoryCardsRsp::Card card;
		};

		struct OpenPlayerCardRsp : ServerPacketData
		{
			uint32_t giftId;
			uint32_t don;
			uint32_t cardAmount; 
			InventoryCardsRsp::Card card;
		};

		struct RoomRandomInvite : ClientPacketData
		{
			uint32_t roomId;
			uint32_t unk_01;
		};

		struct NormalGoodList : ServerPacketData
		{
			struct NormalGood
			{
				uint32_t goodId;
				uint32_t unk_01;
				uint8_t payType;
				uint32_t price;
				uint32_t stock;
				uint8_t category;
			};

			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			NormalGood goods[2460];
		};

		struct BuyItem : ClientPacketData
		{
			uint32_t goodId;
			char unk[18];
		};

		struct BuyItemRsp : ServerPacketData
		{
			uint8_t currencyType;
			uint32_t newAmount;
			uint32_t unk01;
			uint8_t cardCount;
			InventoryCardsRsp::Card card;
		};

		struct Whisper : ClientPacketData
		{
			uint32_t unk_01;
			uint16_t messageLength;
			wchar_t nickname[17];
			wchar_t message[255];
		};
		
		struct WhisperRsp : ServerPacketData
		{
			uint32_t unk_01;
			uint16_t messageLength;
			wchar_t nickname[17];
			wchar_t message[255];
		};

		struct RequestAuth : ClientPacketData
		{
			uint32_t playerId;
		};

		struct RequestAuthResponse : ServerPacketData
		{
			uint32_t playerId;
			uint32_t cmd;
			wchar_t nickname[17];
			uint16_t characterId;
			uint8_t level;
			uint32_t experience;
			uint8_t rank;
			uint16_t prestige;
			uint32_t don;
			uint32_t cash;
			std::array<uint64_t, 13> cardIds;
			std::array<uint32_t, 13> itemIds;
		};

#pragma pack(pop)
	}

	namespace Square
	{
		struct Login : ClientPacketData
		{
			uint32_t uid;
			wchar_t nickname[19];
			char unk[44];
		};
#pragma pack(push, 1)
		struct LoginRsp : ServerPacketData
		{
			struct Park
			{
				char pad01[5];
				uint32_t id;
				uint8_t maxPlayers;
				uint8_t currPlayers;
				uint8_t state;
				wchar_t name[17];
				char pad02[33];
			};

			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			Park park[15];
		};
#pragma pack(pop)
		struct ParkJoin : ClientPacketData
		{
			uint32_t uid;
			uint32_t parkId;
			uint32_t unk_01;
		};


#pragma pack(push, 1)
		struct ParkJoinRsp : ServerPacketData
		{
			uint16_t parkId;
			char pad[7];
			uint32_t parkId2;
			uint8_t maxPlayers;
			uint8_t currPlayers;
			uint8_t state;
			wchar_t name[17];
			char pad01[33];
			std::array<float, 6> position;
		};
#pragma pack(pop)
		struct ParkChangeChannel : ClientPacketData
		{
			uint16_t channelId;
		};

		struct ParkChangeChannelRsp : ServerPacketData
		{
			uint16_t channelId;
			char pad01[6];
		};
		struct ParkMovePlayer : ServerPacketData
		{
			uint32_t targetId;
			uint8_t moveType;
			uint8_t moveDirection;
#pragma pack(push, 2)
			std::array<float, 3> position;
#pragma pack(pop)
#pragma pack(pop)
		};
		struct ParkPlayerMove : ClientPacketData
		{
			uint8_t type;
			uint8_t direction;
#pragma pack(push, 2)
			std::array<float, 3> position;
#pragma pack(pop)
			uint16_t unk_01;
#pragma pack(pop)
		};

		struct ParkAddPlayer : ServerPacketData
		{
			uint32_t state;
			uint32_t id;
			wchar_t name[17];
			uint8_t level;
			uint8_t rank;
			char pad02[2];
			uint16_t characterId;
			std::array<uint32_t, 9> equipment;
			char pad03[4];
			std::array<float, 3> position;
		};
#pragma pack(push, 2)
		struct ParkLoadPlayers : ServerPacketData
		{
			struct SquarePlayer
			{
				uint32_t state;
				uint32_t id;
				wchar_t nickname[17];
				uint8_t level;
				uint8_t rank;
				uint16_t refers;
				uint16_t character;
				std::array<uint32_t, 9> equipment;
				char pad02[6];
				std::array<float, 3> position;
				//char pad03[16];
			};

			uint16_t totalCount;
			uint16_t unknown;
			uint16_t countInPacket;
			SquarePlayer squarePlayer[49];
		};
#pragma pack(pop)
#pragma pack(pop)
		struct ParkRemovePlayer : ServerPacketData
		{
			uint32_t playerToRemove;
		};

		struct ParkPlayerChat : ClientPacketData
		{
			char pad01[34];
			uint16_t messageLength;
			wchar_t message[255];
		};
		struct ParkPlayerChatRsp : ServerPacketData
		{
			wchar_t sender[17];
			uint16_t length;
			wchar_t message[255];
		};
#pragma pack(push,1)
		struct ParkPlayerUpdate : ClientPacketData
		{
			char pad01[4];
			uint16_t characterId;
			std::array<uint32_t, 9> equipment;
			uint32_t unk_01;
			uint32_t unk_02;
		};
		struct ParkUpdatePlayer : ServerPacketData
		{
			uint32_t targetId;
			uint16_t characterId;
			std::array<uint32_t, 9> equipment;
		};
#pragma pack(pop)
		struct ParkPlayerEmote : ClientPacketData
		{
			uint16_t emoteId;
		};
		struct ParkEmotePlayer : ServerPacketData
		{
			uint32_t playerId;
			uint16_t emoteId;
		};

		struct ChangePlayerLevel : ServerPacketData
		{
			uint32_t playerId;
			uint16_t level;
		};

		struct ChangePlayerState : ServerPacketData
		{
			uint32_t playerId;
			uint32_t state;
			uint16_t unk_01;
		};

		struct ParkPlayerJoinBackRsp : ServerPacketData
		{
			std::array<float, 3> position;
		};
#pragma pack(push, 1)
		struct ParkUpdateParkList : ServerPacketData
		{
			uint32_t cmd;
			char pad00[5];
			uint32_t parkId;
			uint8_t maxPlayers;
			uint8_t currPlayers;
			uint8_t state;
			wchar_t name[17];
			char pad01[33];
		};
	};

	namespace Internal {

		struct RequestEquipment : ClientPacketData
		{
			uint32_t playerId;
		};

		struct RequestEquipmentRsp : ServerPacketData
		{
			uint32_t playerId;
			uint8_t rank;
			uint16_t level;
			uint16_t character;
			uint32_t prestige;
			uint8_t status;
			wchar_t nickname[17];
			std::array<uint32_t, 9> equipment;
		};

		struct UpdatePlayerLevel : ClientPacketData
		{
			uint32_t playerId;
			uint16_t level;
		};
		
		struct AnnouncementRsp : ClientPacketData
		{
			wchar_t message[101];
		};
		
		struct Announcement : ServerPacketData
		{
			wchar_t message[101];
		};
		
		struct UpdateGameRoom : ServerPacketData
		{
			uint32_t id;
			uint8_t map;
			uint8_t mode;
			uint8_t currPlayers;
			uint8_t maxPlayers;
			uint8_t meleeOnly;
			uint8_t state;
			wchar_t name[31];
		};

		struct RequestPlayerEquipment : ServerPacketData
		{
			uint32_t playerId;
			uint16_t character;
			uint8_t cmd;
		};

		struct RequestPlayerEquipmentRsp : ServerPacketData
		{
			uint32_t playerId;
			uint16_t character;
			uint8_t cmd;
			std::array<uint32_t, 9> armor;
			std::array<uint32_t, 4> weapons;
		};

	};
#pragma pack(pop)

}; //namespace Packets


#endif //_PACKET_DATA_H