#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class Command {
public:
	enum Rank {
		USER,
		VIP,
		HELPER,
		GM
	};

	Command(std::string name, Command::Rank rank, std::string description);
	~Command();

	inline Command::Rank GetRank() { return _rank; };
	inline std::string Name() { return _name; };
	inline std::string Description() { return _description; };
private:
	Command::Rank _rank;
	std::string _name;
	std::string _description;
};

#endif // !COMMAND_HPP
