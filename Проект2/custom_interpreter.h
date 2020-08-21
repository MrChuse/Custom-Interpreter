#ifndef CUSTOM_INTERPRETER
#define CUSTOM_INTERPRETER

#include <vector>
#include <cstdlib>
#include "command.h"
//#include "brain.h"

/*class InterpreterMutationSettings : public MutationSettings {
	float change_weight_probability = 0.1;
};*/

class Interpreter{
public:

	Interpreter(const std::vector<int> memory, const std::vector<Command> commands, const int max_value, const int limit);

	std::vector<int> make_a_move(std::vector<Cell*> data);

	void mutate(int number_of_brain_changes, float change_gene_probability, float change_brain_size_probability, int max_brain_size_change);

	bool check_ally(Interpreter* other);

	int get_size();

	void set_memory_at(int index, int value);

	void increase_memory_at(int index, int amt);

	void decrease_memory_at(int index, int amt);

	std::vector<int> get_memory() { return memory; }

	std::vector<Command> get_commands() { return commands; }

	int get_max_value() { return max_value; }

	int get_limit() { return limit; }

private:

	std::vector<int> memory;
	std::vector<Command> commands;
	int max_value;
	int limit;

	int pointer;

	float random();
};

#endif