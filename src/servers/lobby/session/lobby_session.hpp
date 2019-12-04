#ifndef _LOBBY_SESSION_H
#define _LOBBY_SESSION_H

#include <memory>
#include <net/session.hpp>
#include "equipment_manager.hpp"
#include "info_manager.hpp"
#include "messenger_manager.hpp"
#include "inventory_manager.hpp"
#include "friend_manager.hpp"
#include "whisper_response_event.hpp"

class Lobby;
class LobbyPacketHandler;

class LobbySession : public Session, std::enable_shared_from_this<LobbySession>
{

public:
	using Ptr = std::shared_ptr<LobbySession>;
	LobbySession(Connection::Ptr connection);
	~LobbySession();
	void HandlePacket(ClientPacket& packet);
	void HandleClose();
	void SetLobby(std::shared_ptr<Lobby> lobby);
	void Save();

	inline EquipmentManager* Equipment() { return _equipmentManager; };
	inline InfoManager* Info() { return _infoManager; };
	inline InventoryManager* Inventory() { return _inventoryManager; }
	inline MessengerManager* Messenger() { return _messengerManager; }
	inline FriendManager* Friends() { return _friendManager; }
	inline std::shared_ptr<Lobby> GetLobby() { return _lobby; };

	void Whisper(std::string message);

	uint32_t userId = NULL;
	LobbyPacketHandler* handler;

private:
	InfoManager* _infoManager;
	EquipmentManager* _equipmentManager;
	InventoryManager* _inventoryManager;
	MessengerManager* _messengerManager;
	FriendManager* _friendManager;
	std::shared_ptr<Lobby> _lobby;
};


#endif //_LOBBY_SESSION_H