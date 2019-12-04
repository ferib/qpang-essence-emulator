#include "command.hpp"

Command::Command(std::string name, Command::Rank rank, std::string description)
{
	_name = name;
	_rank = rank;
	_description = description;
}

Command::~Command()
{
}
