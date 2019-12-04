#ifndef LOBBY_H
#define LOBBY_H

#include <memory>
#include <vector>

#include "connection.hpp"
#include "channel_manager.hpp"
#include "shop_manager.hpp"
#include "leaderboard.hpp"
#include "crane_manager.hpp"
#include "gameroom_manager.hpp"

#include "database.hpp"
#include "offline_player.hpp"
#include <boost/format.hpp>
#include "string_converter.hpp"
#include <string>


class ServerPacket;
class LobbySession;

class Lobby : std::enable_shared_from_this<Lobby> {

public:

	using Ptr = std::shared_ptr<Lobby>;

	Lobby();
	~Lobby();

	void AddSession(std::shared_ptr<LobbySession> session);
	std::shared_ptr<LobbySession> FindSessionByUid(uint32_t userId);
	std::shared_ptr<LobbySession> FindSession(uint32_t playerId);
	std::shared_ptr<LobbySession> FindSession(std::string nickname);
	std::shared_ptr<LobbySession> FindSession(std::array<uint8_t, 16> uuid);
	void RemoveSession(uint32_t userId);

	OfflinePlayer GetOfflinePlayer(uint32_t playerId, OfflinePlayer::Type queryType);
	OfflinePlayer GetOfflinePlayer(std::string nickname, OfflinePlayer::Type queryType);

	void RefreshGamerooms();

	void SendPacket(ServerPacket pack);
	void SendPacket(ServerPacket pack, uint32_t targetId);
	void Notify(std::string message);
	bool IsOnline(uint32_t playerId);
	uint32_t GetItemIdByCardId(uint32_t cardId);

	inline void SetSquareServer(std::shared_ptr<Connection> conn) { _squareServer = conn; };
	void SetAuthServer(std::shared_ptr<Connection> conn);
	void SetRoomServer(std::shared_ptr<Connection> conn);
	inline std::shared_ptr<Connection> GetSquare() { return _squareServer; };
	inline std::shared_ptr<Connection> GetRoom() { return _roomServer; };
	inline std::shared_ptr<Connection> GetAuth() { return _authServer; };
	inline ChannelManager* Channels() { return _channelManager; };
	inline ShopManager* Shop() { return _shopManager; };
	inline Leaderboard* Ranking() { return _leaderBoard; };
	inline CraneManager* Crane() { return _craneManager; };
	inline GameRoomManager* Rooms() { return _roomManager; };
	bool ValidateNickname(std::string nickname);
	inline std::vector<std::shared_ptr<LobbySession>> Sessions() { return _sessions; };

private:
	OfflinePlayer ConstructOfflinePlayer(std::string query, OfflinePlayer::Type queryType);

	std::vector<std::shared_ptr<LobbySession>> _sessions;
	std::shared_ptr<Connection> _squareServer;
	std::shared_ptr<Connection> _authServer;
	std::shared_ptr<Connection> _roomServer;

	ShopManager* _shopManager = new ShopManager();
	ChannelManager* _channelManager = new ChannelManager();
	Leaderboard* _leaderBoard = new Leaderboard();
	CraneManager* _craneManager = new CraneManager();
	GameRoomManager* _roomManager = new GameRoomManager();
};

#endif