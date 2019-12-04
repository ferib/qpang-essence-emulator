#ifndef LOBBY_LOGIN_RESPONSE_EVENT_HPP
#define LOBBY_LOGIN_RESPONSE_EVENT_HPP

#include <cstdint>
#include <memory>

#include "equipment_manager.hpp"
#include "inventory_manager.hpp"
#include "lobby_packet_event.hpp"
#include "friend_manager.hpp"
#include "string_converter.hpp"


class LoginResponseEvent : public LobbyPacketEvent {

public:
	LoginResponseEvent(uint32_t userId) { _userId = userId; };

	ServerPacket Compose(LobbySession* session) override
	{
		Packets::Lobby::LoginRsp response{};

		auto player = session->GetLobby()->FindSessionByUid(_userId);

		//Already logged in, let's disconnect the currenty logged in user.
		if (player != nullptr)
		{
			sLogger->Get()->debug("LoginResponse Already Logged In");

			player->HandleClose();
			player->Disconnect();
		}

		session->userId = _userId;
		session->Info()->Load(_userId);
		session->Equipment()->Load(session->Info()->Id());
		session->Inventory()->Load(session->Info()->Id());
		session->Messenger()->Load(session->Info()->Id());
		session->Friends()->Load(session->Info()->Id());

		response.unknown01 = 299;
		response.uid = session->Info()->Id();
		response.don = session->Info()->Don();
		response.cash = session->Info()->Cash();
		response.coins = session->Info()->Coins();
		response.level = session->Info()->Level();
		response.experience = session->Info()->Experience();
		response.rank = session->Info()->Rank();
		response.defaultCharacter = session->Info()->Character();
		response.inventoryCapacity = MAX_INVENTORY;
		response.acceptPm = true;
		response.acceptFriendRequests = true;
		response.acceptInvites = true;
		response.acceptTradeRequests = true;
		response.memoListDailyCapacity = 20;
		response.memosLeft = 19;
		response.friendListOutgoingCapacity = MAX_FRIENDS;
		response.friendListCapacity = MAX_FRIENDS;

		std::string nickname = session->Info()->Nickname();
		wcsncpy(response.nickname, std::wstring(nickname.begin(), nickname.end()).data(), 16);
		
		std::array<std::array<uint64_t, 13>, 6> allEquipment = session->Equipment()->GetAll();
		for (size_t i = 0; i < EquipmentManager::CHARACTER_COUNT; i++)
		{
			Packets::Lobby::LoginRsp::CharacterEquipment equipment = response.equipment[i];
			std::array<uint64_t, 13> characterEquipment = allEquipment[i];

			equipment.characterId = session->Equipment()->GetCharacterCode(i);
			equipment.hair.cardId = characterEquipment[EquipmentManager::HEAD];
			equipment.face.cardId = characterEquipment[EquipmentManager::FACE];
			equipment.body.cardId = characterEquipment[EquipmentManager::BODY];
			equipment.hands.cardId = characterEquipment[EquipmentManager::HAND];
			equipment.pants.cardId = characterEquipment[EquipmentManager::BOTTOM];
			equipment.shoes.cardId = characterEquipment[EquipmentManager::FOOT];
			equipment.back.cardId = characterEquipment[EquipmentManager::BACK];
			equipment.side.cardId = characterEquipment[EquipmentManager::SIDE];
			equipment.primaryWeapon.cardId = characterEquipment[EquipmentManager::PRIMARY];
			equipment.secondaryWeapon.cardId = characterEquipment[EquipmentManager::SECONDARY];
			equipment.throwWeapon.cardId = characterEquipment[EquipmentManager::THROW];
			equipment.meleeWeapon.cardId = characterEquipment[EquipmentManager::MELEE];

			response.equipment[i] = equipment;
		}
		return ServerPacket::Create<Opcode::LOBBY_LOGIN_RSP>(response);
	};
private:
	uint32_t _userId;
};

#endif