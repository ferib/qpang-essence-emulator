#ifndef _GAME_NET_INTERFACE_HPP
#define _GAME_NET_INTERFACE_HPP

//tnl
#include <tnl/tnl.h>
#include <tnl/tnlNetInterface.h>
#include <tnl/tnlNetConnection.h>
#include <tnl/tnlBitStream.h>
#include <tnl/tnlClientPuzzle.h>
#include <tnl/tnlCertificate.h>
#include <libtomcrypt/mycrypt.h>

//std
#include <map>

using namespace TNL;

class GameNetInterface : public NetInterface
{
	typedef NetInterface Parent;

public:
	GameNetInterface(const Address &bindAddress);
	~GameNetInterface() = default;
	void ProcessPacket(const Address &sourceAddress, BitStream *packetStream);
};

#endif //_GAME_NET_INTERFACE_HPP
