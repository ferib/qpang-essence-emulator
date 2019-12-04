#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <cstdint>


struct Message {
	
	Message() { this->id = NULL; };
	Message(uint32_t id, uint32_t senderId, std::string senderName, std::string messageBody, uint32_t received, uint8_t opened)
	{
		this->id = id;
		this->senderId = senderId;
		this->senderName = senderName;
		this->messageBody = messageBody;
		this->received = received;
		this->opened = opened;
	}
	
	uint32_t id;
	uint32_t senderId;
	std::string senderName;
	std::string messageBody;
	uint32_t received;
	uint8_t opened;
};

#endif