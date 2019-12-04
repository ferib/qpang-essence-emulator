#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <memory>
#include <cstdint>
#include <string>

class Response : public std::enable_shared_from_this<Response> {
	
public:
	Response(uint16_t statusCode, std::string body) { _statusCode = statusCode; _body = body; };
	~Response() {};

	uint16_t Status() { return _statusCode; };
	std::string Head() { return _head; };
	std::string Body() { return _body; };
private:
	uint16_t _statusCode;
	std::string _head;
	std::string _body;
};


#endif // !RESPONSE_HPP
