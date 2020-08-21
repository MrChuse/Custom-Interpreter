#ifndef COMMAND
#define COMMAND

// #include "brain.h"
#include <vector>
#include "field.h"
#include "cell.h"

class Command {
public:

	int parameters_number;
	bool is_final;
	int(*conditional)(std::vector<Cell*> data, std::vector<int> command_and_arguments);

	Command(int param_num, bool fin, int (*conditional)(std::vector<Cell*> data, std::vector<int> command_and_arguments) = nullptr) {
		parameters_number = param_num;
		is_final = fin;
		this->conditional = conditional;
	}
};

#endif