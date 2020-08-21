#include "custom_interpreter.h"
#include "field.h" // wtf this isn't right (I need it to get Cell* in make_a_move)
Interpreter::Interpreter(const std::vector<int> memory, const std::vector<Command> commands, const int max_value, const int limit) {
	this->memory = std::vector<int>(memory);
	this->commands = std::vector<Command>(commands);
	this->limit = limit;
	this->max_value = max_value;

	pointer = 0;
}

std::vector<int> Interpreter::make_a_move(std::vector<Cell*> data) {

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

void Interpreter::mutate(int number_of_brain_changes, float change_gene_probability, float change_brain_size_probability, int max_brain_size_change) {
	for (int i = 0; i < number_of_brain_changes; i++) {
		if (random() < change_gene_probability) {
			int gene = int(random() * memory.size());
			memory[gene] = int(random() * max_value);
			if (random() < change_brain_size_probability) {
				int dsize = int(random() * (2 * max_brain_size_change + 1)) - max_brain_size_change;
				if (dsize == 0)
					return;
				if (dsize > 0)
					for (int j = 0; j < dsize; j++)
						memory.push_back(int(random() * max_value));
				else
					for (int j = 0; j < dsize; j++)
						memory.erase(memory.begin() + int(random() * memory.size()));
			}
		}
	}
}

bool Interpreter::check_ally(Interpreter* other) { return false; }

int Interpreter::get_size() { return memory.size(); }

void Interpreter::set_memory_at(int index, int value) {
	memory[index] = value % max_value;
}

void Interpreter::increase_memory_at(int index, int amt) {
	memory[index] = (memory[index] + amt) % max_value;
}

void Interpreter::decrease_memory_at(int index, int amt) {
	memory[index] = (memory[index] + max_value - amt) % max_value;
}

float Interpreter::random() {
	return 1.f * rand() / RAND_MAX;
}