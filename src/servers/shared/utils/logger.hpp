#ifndef SHARED_LOGGER_HPP
#define SHARED_LOGGER_HPP

#include <string>
#include <memory>
#include "spdlog/spdlog.h"

class Logger {

public:

	static Logger* Instance()
	{
		static Logger logger;
		return &logger;
	}

	void Init(std::string name);
	std::shared_ptr<spdlog::logger> Get();
private:
	std::shared_ptr<spdlog::logger> _logger;
};

#define sLogger Logger::Instance()

#endif