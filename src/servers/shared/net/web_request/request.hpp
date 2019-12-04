#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "response.hpp"
#include <string>
#include <list>
#include <cstdint>
#include <map>
#include <memory>
#include "settings_manager.hpp"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

class Request {
public:
	Request(std::string endPoint);
	~Request();

	Response Post(std::map<std::string, std::string> fields);
	Response Get();

private:
	std::string _endPoint;
	std::list<std::string> _headers;
	std::string _apiKey;
};


#endif // !REQUEST_HPP
