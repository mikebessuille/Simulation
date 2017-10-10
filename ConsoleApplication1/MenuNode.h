#pragma once

#include <string>
#include <vector>

class MenuNode
{
public:
	MenuNode(	const std::string&, const std::string&,
				const std::vector<std::pair<std::string, std::string>>&
					= std::vector<std::pair<std::string, std::string>>{}); // default value is an empty vector
	~MenuNode();

	const std::string& takeChoice() const;
	bool operator==(const std::string&) const;

private:
	std::string _name, _prompt;
	std::vector<std::pair<std::string, std::string>> _choices;
};
