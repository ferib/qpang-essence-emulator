#ifndef GC_SCORE_RESULT_HPP
#define GC_SCORE_RESULT_HPP

#include "game_net_event.hpp"
#include <vector>
#include "player.hpp"
#include <numeric>

class GCScoreResult : public GameNetEvent
{
	typedef NetEvent Parent;
public:

	GCScoreResult() : GameNetEvent{ GC_SCORE_RESULT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCScoreResult(std::vector<Player::Ptr> players) : GameNetEvent{ GC_SCORE_RESULT, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirServerToClient }
	{
		count = players.size();

		for (auto player : players)
		{
			//scorePlayers.push_back(ScorePlayer{ player->Info()->Id(), 0, 1, player->Info()->Team(),
			//	0, player->Info()->GainedKills(), player->Info()->GainedDeaths(), 0,
			//player->Info()->GainedDon(), player->Info()->GainedExperience(), 0, 0, 0, 0, 0, 3, 0, 0,
			//GetBuffer(player->Info()->Nickname()), 0 });
			//
			//player->Info()->Team() == RoomInfoManager::BLUE ? totalValueBlue += player->Info()->Kills() : totalValueYellow += player->Info()->Kills();
		}
	};

	void pack(EventConnection* conn, BitStream* bstream)
	{
		bstream->write(U16(totalValueBlue)); // total essence blue
		bstream->write(U16(totalValueBlue)); // total kills blue
		bstream->write(U16(0)); // total deaths blue
		bstream->write(U16(totalValueYellow)); // total essence yellow
		bstream->write(U16(totalValueYellow)); // total kills yellow
		bstream->write(U16(0)); // total deaths yellow
		bstream->write(U16(0));
		bstream->write(U16(0));
		bstream->write(U16(sGame->ExpRate())); // global exp boost? (is added on top of the multiplier in GCScoreResult::Player)
		bstream->write(U16(0));
		bstream->write(U16(0));
		bstream->write(U16(0));
		bstream->write(U8(count));
		bstream->write(U32(0));

		for (auto& player : scorePlayers)
		{
			bstream->write(player.uid);
			bstream->write(player.unk_02);
			bstream->write(player.unk_03);
			bstream->write(player.team);
			bstream->write(player.essenceTime);
			bstream->write(player.kills);
			bstream->write(player.deaths);
			bstream->write(player.unk_08);
			bstream->write(player.donEarned);
			bstream->write(player.expEarned);
			bstream->write(player.unk_11);
			bstream->write(player.unk_12);
			bstream->write(player.luckySackCount);
			bstream->write(player.unk_14);
			bstream->write(player.unk_15);
			bstream->write(player.unk_16);
			bstream->write(player.donMultiplier);
			bstream->write(sGame->ExpRate());
			bstream->write(player.buffer);
			bstream->write(player.unk_19);
		}
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	struct ScorePlayer {
		U32 uid = 0;
		U16 unk_02 = 0;
		U8 unk_03 = 1;
		U8 team = 1; // 1 = team blue, 2 = team yellow
		U16 essenceTime = 121;
		U16 kills = 20;
		U16 deaths = 3;
		U16 unk_08 = 0;
		U32 donEarned = 777;
		U32 expEarned = 666;
		U32 unk_11 = 0; // weird (B) thingy
		U8 unk_12 = 1; // achievement earned?
		U8 luckySackCount = 12; // LuckySacks are the event items that fell out of the sky during events
		U8 unk_14 = 0;
		U8 unk_15 = 0;
		U8 unk_16 = 3; // which boosts are active? 1 = xp booster, 2 = don boost so 3 = xp & cash boosts?
		U16 donMultiplier = 50; // in %
		U16 expMultiplier = 100; // in %
		ByteBuffer* buffer;
		U32 unk_19 = 0;
	};

	U8 count = 0;

	std::vector<ScorePlayer> scorePlayers;
	uint32_t totalValueBlue = 0;
	uint32_t totalValueYellow = 0;

	TNL_DECLARE_CLASS(GCScoreResult);
};

#endif // !GC_ARRANGED_ACCEPT_HPP