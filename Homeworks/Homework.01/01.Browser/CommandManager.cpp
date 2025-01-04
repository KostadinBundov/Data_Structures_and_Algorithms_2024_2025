#include "CommandManager.h"

std::vector<std::string> CommandManager::parseCommand(const std::string& command) const {
	std::stringstream ss(command);
	std::string arg;
	std::vector<std::string> args;

	while (ss >> arg) {
		if (!arg.compare("$")) {
			continue;
		}

		args.push_back(arg);
	}

	return args;
}

SortCriteria CommandManager::parseCriteria(const std::string& command) const {
	return command.compare("TIME") == 0 ? SortCriteria::TIME : SortCriteria::URL;
}

void CommandManager::execute(const std::string& command) {
	std::vector<std::string> args = parseCommand(command);

	if (!args[0].compare("GO")) {
		browser.go(args[1]);
	}
	else if (!args[0].compare("INSERT")) {
		browser.insert(args[1]);
	}
	else if (!args[0].compare("BACK")) {
		browser.back();
	}
	else if (!args[0].compare("FORWARD")) {
		browser.forward();
	}
	else if (!args[0].compare("REMOVE")) {
		browser.remove();
	}
	else if (!args[0].compare("PRINT")) {
		browser.print();
	}
	else if (!args[0].compare("SORT")) {
		SortCriteria criteria = parseCriteria(args[1]);
		browser.sort(criteria);
	}
}
