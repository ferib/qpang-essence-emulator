#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <map>
#include <string>
#include "command.hpp"

template<typename CommandType>
class CommandHandler {
public:
	CommandHandler() {};
	~CommandHandler() {};
protected:
	virtual void Set(std::string commandName, CommandType* command) { _commands[commandName] = command; };
	virtual void TryExecute(std::string commandName) {};
	std::map<std::string, CommandType*> _commands;
};



#endif // !COMMAND_HANDLER_HPP
