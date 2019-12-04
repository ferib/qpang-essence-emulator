//NOTE: this is only for testing purposes, will go away later

#ifndef ACCOUNTS_HPP
#define ACCOUNTS_HPP

#include <string>
#include <vector>
#include <cstdint>

#include "boost/optional.hpp"

struct Account
{
	uint32_t id;
	std::wstring loginId;
	std::wstring password;
	std::wstring nickname;
	uint32_t characterId;
	uint32_t level;
	uint32_t rank;
	uint32_t don;
	uint32_t cash;
	float x;
	float y;
	float z;
};

static std::vector<Account> accountList = { 
};

static boost::optional<Account> GetAccount(const uint32_t accountId)
{
	for (auto& a : accountList)
	{
		if (a.id == accountId)
		{
			return a;
		}
	}

	return {};
}

static boost::optional<Account> GetAccount(const std::wstring loginId)
{
	for (auto& a : accountList)
	{
		if (a.loginId == loginId)
		{
			return a;
		}
	}

	return {};
}


#endif //ACCOUNTS_HPP