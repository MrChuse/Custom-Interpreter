#ifndef CUSTOM_INTERPRETER
#define CUSTOM_INTERPRETER

#include <vector>
#include "command.h"
#include "brain.h"

class Interpreter : public Brain {
public:

	Interpreter(const std::vector<int> memory, const std::vector<Command> commands, const int max_value, const int limit);

	std::vector<int> make_a_move(SensorData data) override;

	void mutate(MutationSettings settings) override;

	bool check_ally(Brain* other) override;

	int get_size() override;

	void set_memory_at(int index, int value);

	void increase_memory_at(int index, int amt);

	void decrease_memory_at(int index, int amt);

private:

	std::vector<int> memory;
	std::vector<Command> commands;
	int max_value;
	int limit;

	int pointer;
};

#endif