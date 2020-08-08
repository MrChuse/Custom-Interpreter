#include "custom_interpreter.h"
#include <iostream>

int test(std::vector<int> memory, std::vector<std::vector<int>> correct, int id) {
	std::cout << id << std::endl;
	Command photosynthesis = Command(0, true, nullptr);
	Command eat = Command(1, true, nullptr);
	Command com10 = Command(10, true, nullptr);

	std::vector<Command> commands = { photosynthesis, eat, com10 };
	SensorData data;

	Interpreter brain = Interpreter(memory, commands, 10);
	for (int i = 0; i < correct.size(); i++) {
		std::vector<int> ans = brain.make_a_move(data);

		bool f = false;
		for (int j = 0; j < ans.size(); j++) {
			if (correct[i][j] != ans[j]) {
				f = true;
				break;
			}
		}
		if (f) {
			std::cout << "move number " << i << " correct: ";
			for (int j = 0; j < correct[i].size(); j++)
				std::cout << correct[i][j] << " ";
			std::cout << ", but answer was ";
			for (int j = 0; j < ans.size(); j++)
				std::cout << ans[j] << std::endl;
			system("pause");
			return -1;
		}
	}
}

void run_tests() {
	std::cout << "HELLO WORLD------------------------------------------" << std::endl;

	std::vector<int> memory = { 0, 0, 0, 1, 10 };
	std::vector< std::vector<int> > correct = { { 0 },{ 0 },{ 0 },{ 1, 10 },{ 0 },{ 0 },{ 0 },{ 1, 10 } };
	test(memory, correct, 1);

	memory = { 0 };
	correct = { { 0 },{ 0 },{ 0 },{ 0 } };
	test(memory, correct, 2);

	memory = { 11, 0, 0, 1 };
	correct = { { 0 },{ 0 },{ 1, 11 },{ 0 },{ 0 },{ 1, 11 } };
	test(memory, correct, 2);

	memory = { 2, 0 };
	correct = { { 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2 },{ 0 } };
	test(memory, correct, 3);
}

int main() {
	run_tests();

	system("pause");
	return 0;
}