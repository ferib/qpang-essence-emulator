#include "square_session.hpp"

#include "square_packet_handler.hpp"
#include <packets/packet_data.hpp>

SquareSession::SquareSession(Connection::Ptr connection)
	: Session{ connection }
{
	_connection->SetHandlers(
		std::bind(&SquareSession::HandlePacket, this, std::placeholders::_1),
		std::bind(&SquareSession::HandleClose, this));

	_infoManager = new InfoManager();
}

SquareSession::~SquareSession()
{
	printf("destroyed %d \n", Info()->Id());
}

void SquareSession::HandlePacket(ClientPacket& packet)
{
	if (_connection)
	{
		if (_connection->state == Connection::State::CONNECTED)
			handler->Execute(this, packet);
	}
}

void SquareSession::HandleClose()
{
	if (GetSquare())
		GetSquare()->RemovePlayer(Info()->Id());

	_manager->RemoveSession(Info()->Id());
}

void SquareSession::Whisper(std::string message)
{
	Send(ChatResponseEvent{ Info()->Nickname(), std::string("(Whisper): ").append(message) }.Compose(this));
}
