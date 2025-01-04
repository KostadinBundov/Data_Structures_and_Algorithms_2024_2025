#include "CommandManager.h"

int main() {
	CommandManager commandManager;
	std::string command;

	while (true) {
		std::getline(std::cin, command);

		if (command == "END") {
			break;
		}

		commandManager.execute(command);
	}
}