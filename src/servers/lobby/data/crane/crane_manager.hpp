#ifndef CRANE_MANAGER_HPP
#define CRANE_MANAGER_HPP

#include <cstdint>
#include <vector>
#include "crane_item.hpp"


class CraneManager {

public:
	CraneManager();
	~CraneManager();
	void Load();
	CraneItem Use();

private:
	std::vector<CraneItem> _items;
};

#endif // !CRANE_MANAGER_HPP
