#include "packet.hpp"

//std
#include <array>
#include <iostream>


ClientPacket::ClientPacket()
	: header{ 0 }
{
}

ServerPacket::ServerPacket(Opcode opcode, size_t length)
	: header{ 0 }
{
	buffer.resize(length + 4);
	WritePayloadHeader({ static_cast<uint16_t>(length + 4), opcode });
	header.fullLength = static_cast<uint16_t>(length + 8);
}

ServerPacket::ServerPacket()
	: header{ 0 }
{

}


void ServerPacket::AppendChecksum()
{
	static std::array<uint8_t, 8> checksumBytes = { 0x9C, 0x14, 0xED, 0x29, 0xF2, 0xB5, 0x83, 0x7A };

	uint16_t extra = (buffer.size() + 2) & 7;
	if (!extra)
	{
		return;
	}

	if (extra == 8)
	{
		std::cout << "extra = " << extra << "\n";
		return;
	}

	uint16_t amount = 8 - extra;
	//buffer.resize(buffer.size() + amount + 2);
	for (uint16_t i{ 0 }; i < amount; ++i)
	{
		buffer.push_back(buffer[i] ^ checksumBytes[i]);
	}

	buffer.push_back(static_cast<uint8_t>(amount & 0xFF));
	buffer.push_back(static_cast<uint8_t>((amount >> 8) & 0xFF));
}

ServerPacket ServerPacket::MakeCopy()
{
	ServerPacket packet{};
	packet.header = header;
	packet.buffer = buffer;
	return packet;
}