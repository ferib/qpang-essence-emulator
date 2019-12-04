#ifndef _PACKET_H
#define _PACKET_H

//std
#include <cstdint>
#include <cstring>
#include <vector>


//this
#include "opcodes.hpp"


struct PacketHeader
{
	//Full length (this header + payload + crc)
	uint16_t fullLength; //0 
	uint8_t encrypted; //2
	uint8_t unknown_02; //3
};


struct PayloadHeader
{
	//Full length (this header + payload + crc)
	uint16_t length; //0 
	Opcode opcode;
};

class ClientPacket
{
public:

	//Size: 4
	struct PayloadHeader
	{
		//Length of the payload, including the header
		uint16_t length; //4 
		Opcode opcode; //6
	};

	struct ReadException : public std::exception
	{
		const char* what() const throw ()
		{
			return "Client Packet Read Exception";
		}
	};


	ClientPacket();
	//First 4 bytes of the payload: payload header
	template<typename T>
	T Read(size_t posInBuffer = 4)
	{
		if (buffer.size() >= sizeof(T))
		{
			return *reinterpret_cast<T*>(buffer.data() + posInBuffer);
		}
		return T{};
	}

	PayloadHeader ReadPayloadHeader()
	{
		return Read<PayloadHeader>(0);
	}

	bool Check()
	{
		//basic check for now
		auto payloadHeader = ReadPayloadHeader();
		if (payloadHeader.length != header.fullLength - 4)
		{
			return false;
		}

		return true;
	}

	PacketHeader header;
	std::vector<char> buffer;
	
};



class ServerPacket
{
public:


	ServerPacket(Opcode opcode, size_t length);
	ServerPacket();
	template<typename T>
	void Write(T& data, size_t posInBuffer = 4)
	{
		std::memcpy(buffer.data() + posInBuffer, &data, sizeof(T));
	}


	PayloadHeader ReadPayloadHeader()
	{
		return *reinterpret_cast<PayloadHeader*>(buffer.data());
	}

	void WritePayloadHeader(const PayloadHeader& header)
	{
		if (buffer.size() < 4)
		{
			buffer.resize(4);
		}
		//*reinterpret_cast<PayloadHeader*>(buffer.data()) = header;
		Write(header, 0);
	}

	template<Opcode Op, typename T>
	static ServerPacket Create()
	{
		ServerPacket packet{ Op, sizeof(T) };
		return packet;
	}

	template<Opcode Op, typename T>
	static ServerPacket Create(const T& data)
	{
		ServerPacket packet{ Op, sizeof(T) };
		packet.Write(data);
		return packet;
	}


	template<Opcode Op>
	static ServerPacket CreateErrorPacket(uint16_t errCode)
	{
		ServerPacket packet{ Op, 8 };
		packet.Write(errCode, 8);
		return packet;
	}

	ServerPacket MakeCopy();

	void AppendChecksum();

	PacketHeader header;
	std::vector<char> buffer;
};


#endif //_PACKET_H