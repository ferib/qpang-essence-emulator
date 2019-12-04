#ifndef GC_PLAYER_CHANGE_HPP
#define GC_PLAYER_CHANGE_HPP

#include "game_net_event.hpp"
#include <array>

class GCPlayerChange : public GameNetEvent
{
	typedef NetEvent Parent;

public:
	GCPlayerChange() : GameNetEvent{ GC_PLAYER_CHANGE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } {};
	GCPlayerChange(const Player::Ptr& player, const U8& cmd, const U32& value) : GameNetEvent{ GC_PLAYER_CHANGE, NetEvent::GuaranteeType::GuaranteedOrdered, NetEvent::DirAny } 
	{
		this->playerId = player->GetIdentifier();
		this->cmd = cmd;
		this->value = value;
		this->equipment = player->GetEquipment()->GetArmor();
	};
	void pack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->write(playerId);
		bstream->write(cmd);
		bstream->write(value);

		for (size_t i = 0; i < 9; i++)
		{
			bstream->write(U32(equipment.at(i)));
		}
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 playerId;
	U8 cmd;
	U32 value;

	std::array<uint32_t, 9> equipment;

	TNL_DECLARE_CLASS(GCPlayerChange);
};

#endif // !GC_ARRANGED_ACCEPT_HPP