#ifndef COMMAND
#define COMMAND

#include "sensor_data.h"

class Command {
public:

	int parameters_number;
	bool is_final;
	int(*conditional)(SensorData data, std::vector<int> command_and_arguments);

	Command(int param_num, bool fin, int (*conditional)(SensorData data, std::vector<int> command_and_arguments)) {
		parameters_number = param_num;
		is_final = fin;
		this->conditional = conditional;
	}
};

#endif