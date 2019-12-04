#ifndef GC_SCORE_HPP
#define GC_SCORE_HPP

#include <memory>
#include <vector>
#include <time.h>

#include "game_room_session.hpp"
#include "game_net_event.hpp"
#include "score_board.hpp"

class GCScore : public GameNetEvent
{
	typedef NetEvent Parent;

public:

	struct ScorePlayer
	{
		U32 playerId;
		U16 team;
		U8 hidden;
		U16 level;
		U16 kills;
		U16 deaths;
		U16 essence;
		U8 team2;
		ByteBuffer* nickname;
		U32 unk_01;
	};

	GCScore() : GameNetEvent{ GC_SCORE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};

	GCScore(const U8& cmd) : GameNetEvent{ GC_SCORE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny }
	{
		this->cmd = cmd;
	};

	GCScore(std::shared_ptr<GameRoomSession> room, bool byGame) : GameNetEvent{ GC_SCORE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{

		if (room == nullptr)
			return;

		auto scoreBoard = room->GenerateScoreBoard();

		this->cmd = byGame ? -56 : 1;
		this->m_players = scoreBoard.GetResults();
	};
	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(cmd);
		bstream->write(unk_02);
		bstream->write(blueTotalKill);
		bstream->write(blueTotalDeath);
		bstream->write(unk_03);
		bstream->write(yellowTotalKill);
		bstream->write(yellowTotalDeath);
		bstream->write(unk_04);
		bstream->write((U8)m_players.size());

		for(auto& player : m_players)
		{
			bstream->write(U32(player.id));
			bstream->write(U16(player.level));
			bstream->write(U8(false));
			bstream->write(U16(0));
			bstream->write(U16(player.kills));
			bstream->write(U16(player.deaths));
			bstream->write(U16(player.score));
			bstream->write(U8(player.team));
			WriteBuffer(bstream, player.name);
			bstream->write((U32)0);
		}
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	std::vector<ScoreBoard::Player> m_players;
	U8 cmd = -56;
	U16 unk_02 = 0;
	U16 blueTotalKill = 0;
	U16 blueTotalDeath = 0;
	U16 unk_03 = 0;
	U16 yellowTotalKill = 0;
	U16 yellowTotalDeath = 0;
	U32 unk_04 = 1;

	TNL_DECLARE_CLASS(GCScore);

};
#endif // !GC_ARRANGED_ACCEPT_HPP