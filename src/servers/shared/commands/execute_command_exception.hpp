#ifndef EXECUTE_COMMAND_EXCEPTION_HPP
#define EXECUTE_COMMAND_EXCEPTION_HPP

#include <exception>
#include <string>

struct ExecuteCommandException : public std::exception
{
	ExecuteCommandException(std::string exceptionMessage)
	{
		this->exceptionMessage = exceptionMessage;
	}

	const char* what() const throw ()
	{
		return exceptionMessage.c_str();
	}

	std::string exceptionMessage;
};

#endif // !EXECUTE_COMMAND_EXCEPTION_HPP