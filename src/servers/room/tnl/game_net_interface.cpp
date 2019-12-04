#include "game_net_interface.hpp"

//std
#include <iostream>
#include <algorithm>

GameNetInterface::GameNetInterface(const Address &bindAddress)
	: NetInterface(bindAddress)
{
}


void GameNetInterface::ProcessPacket(const Address &sourceAddress, BitStream *packetStream)
{
	Parent::processPacket(sourceAddress, packetStream);
}

