#ifndef TEST_COMMAND_HPP
#define TEST_COMMAND_HPP

#include "square_command.hpp"

class TestCommand : public SquareCommand
{
public:
	TestCommand() : SquareCommand("Test Command", Rank::GM, "This is a test command") {};

	void Execute(SquareSession* session)
	{
		session->Whisper("Idk");
	};
};

#endif