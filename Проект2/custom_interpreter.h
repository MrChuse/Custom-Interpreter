#ifndef CUSTOM_INTERPRETER
#define CUSTOM_INTERPRETER

#include <vector>
#include "command.h"
#include "sensor_data.h"

class Interpreter {
public:

	Interpreter(const std::vector<int> memory, const std::vector<Command> commands, const int limit);

	std::vector<int> make_a_move(SensorData data);

private:

	std::vector<int> memory;
	std::vector<Command> commands;
	int limit;

	int pointer;
};

#endif