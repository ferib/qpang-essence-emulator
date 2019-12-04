#include "square.hpp"
#include "square_session.hpp"
#include "remove_player_event.hpp"|
#include "update_list_event.hpp"
#include "square_manager.hpp"

Square::Square()
{
}

Square::Square(uint32_t id, std::string name, uint32_t maxCapacity)
{
	_id = id;
	_name = name;
	_maxCapacity = maxCapacity;
}

Square::~Square()
{
}

void Square::SendPacket(ServerPacket pack, uint32_t playerId)
{
	for (auto session : _sessions)
		if(session->Info()->Id() != playerId)
			session->Send(pack);
}

bool Square::AddPlayer(std::shared_ptr<SquareSession> session)
{
	auto foundPlayer = GetPlayer(session->Info()->Id());
	if (foundPlayer != nullptr)
		return false;

	sLogger->Get()->debug("Adding {0} to square {1:d}", session->Info()->Nickname(), Id());

	_sessions.push_back(session);
	session->SetSquare(weak_from_this());
	session->GetSquareManager()->Broadcast(UpdateListEvent{ shared_from_this(), UpdateListEvent::UPDATE }.Compose(nullptr));
	return true;
}

void Square::RemovePlayer(uint32_t playerId)
{
	for (auto it = _sessions.begin(); it != _sessions.end(); it++)
	{
		if ((*it)->Info()->Id() == playerId)
		{
			sLogger->Get()->debug("Removed {0} from square {1:d}", (*it)->Info()->Nickname(), Id());
			auto squareManager = (*it)->GetSquareManager();
			_sessions.erase(it);

			if (_sessions.size() < 1)
				squareManager->Broadcast(UpdateListEvent{ shared_from_this(), UpdateListEvent::REMOVE }.Compose(nullptr));
			else
				squareManager->Broadcast(UpdateListEvent{ shared_from_this(), UpdateListEvent::UPDATE }.Compose(nullptr));

			break;
		}
	}

	SendPacket(RemovePlayerEvent{ playerId }.Compose(nullptr));
}

std::shared_ptr<SquareSession> Square::GetPlayer(uint32_t playerId)
{
	for (auto session : _sessions)
		if (session->Info()->Id() == playerId)
			return session;

	return nullptr;
}

std::vector<std::shared_ptr<SquareSession>> Square::List()
{		
	return _sessions;
}
