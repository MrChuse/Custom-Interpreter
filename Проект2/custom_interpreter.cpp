#include "custom_interpreter.h"
Interpreter::Interpreter(const std::vector<int> memory, const std::vector<Command> commands, const int limit) {
	this->memory = std::vector<int>(memory);
	this->commands = std::vector<Command>(commands);
	this->limit = limit;

	pointer = 0;
}

std::vector<int> Interpreter::make_a_move(SensorData data) {

	// execute no more than *limit* non-final commands
	int command_counter = 0;
	while (command_counter < limit) {
		int current_command_id = memory[pointer];

		//check if data has its command
		if (current_command_id >= commands.size()) {
			pointer = (pointer + 1) % memory.size();
			command_counter++;
			continue;
		}

		int left = pointer;
		int right = pointer + commands[current_command_id].parameters_number + 1; // +1 to compensate for right boundary

																				  // copy the command id and its arguments to return
		std::vector<int> command_and_arguments = std::vector<int>(right - left);
		command_and_arguments.clear();
		if (right < memory.size()) {
			for (int i = left; i < right; i++) {
				command_and_arguments.push_back(memory[i]);
			}
		}
		else {
			// copy from left boundary to last element of memory
			for (int i = left; i < memory.size(); i++) {
				command_and_arguments.push_back(memory[i]);
			}
			right -= memory.size();

			// copy full array until right is smaller than memory size
			while (right >= memory.size()) {
				for (int i = left; i < memory.size(); i++)
					command_and_arguments.push_back(memory[i]);
				right -= memory.size();
			}

			//copy the remaining part from 0 to right
			for (int i = 0; i < right; i++)
				command_and_arguments.push_back(memory[i]);
		}

		if (commands[current_command_id].is_final) {
			pointer = right;
			return command_and_arguments;
		}
		else {
			int shift = commands[current_command_id].conditional(data, command_and_arguments);
			pointer = (pointer + shift) % memory.size();
			command_counter++;
			continue;
		}

	}

	return std::vector<int>(1, 0);
}