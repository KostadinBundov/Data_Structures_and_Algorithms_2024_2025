#pragma once
#include "Browser.h"
#include <iostream>
#include <sstream>
#include "SortCriteria.h"
#include <vector>

class CommandManager {
private:
	Browser browser;

	std::vector<std::string> parseCommand(const std::string& command) const;
	SortCriteria parseCriteria(const std::string& command) const;
public:
	void execute(const std::string& command);
};