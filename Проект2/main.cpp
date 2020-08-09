#include "custom_interpreter.h"
#include "field.h"
#include <iostream>

int test_interpreter(std::vector<int> memory, std::vector<std::vector<int>> correct, int id) {
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
	return 0;
}

int test_temperature(int id) {
	std::cout << id << std::endl;
	Field f = Field(10, 10, 100);
	std::vector<int> correct = { 0, 6, 12, 19, 25, 32, 38, 44, 51, 57 };
	std::vector<std::vector<Cell>> field = f.get_field();
	for (int i = 0; i < 10; i++) {
		if (field[i][i].get_temperature() != correct[i]) {
			std::cout << "Incorrect! Correct was " << correct[i] << " but output was " << field[i][0].get_temperature() << std::endl;
		}
	}
	return 0;
}

int test_agents_empty(int id) {
	std::cout << id << std::endl;
	Field f = Field(10, 10, 100);
	std::vector<std::vector<Cell>> field = f.get_field();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j].is_occupied()) {
				std::cout << "Somehow " << i << ", " << j << " is occupied" << std::endl;
				return -1;
			}
		}
	}
	return 0;
}

void test_case_interpreter() {
	std::cout << "interpreter tests started" << std::endl;

	std::vector<int> memory = { 0, 0, 0, 1, 10 };
	std::vector< std::vector<int> > correct = { { 0 },{ 0 },{ 0 },{ 1, 10 },{ 0 },{ 0 },{ 0 },{ 1, 10 } };
	test_interpreter(memory, correct, 1);

	memory = { 0 };
	correct = { { 0 },{ 0 },{ 0 },{ 0 } };
	test_interpreter(memory, correct, 2);

	memory = { 11, 0, 0, 1 };
	correct = { { 0 },{ 0 },{ 1, 11 },{ 0 },{ 0 },{ 1, 11 } };
	test_interpreter(memory, correct, 3);

	memory = { 2, 0 };
	correct = { { 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2 },{ 0 } };
	test_interpreter(memory, correct, 4);

	std::cout << "interpreter tests ended" << std::endl << std::endl;
}

void test_case_field() {
	std::cout << "Field tests started" << std::endl;
	
	test_temperature(1);

	std::cout << "Field tests ended" << std::endl << std::endl;
}

void run_tests() {
	std::cout << "-------------------tests started-----------------------" << std::endl;

	test_case_interpreter();

	test_case_field();
}

int main() {
	run_tests();

	system("pause");
	return 0;
}

/*#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(10, 10);

	float t = 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		shape.setScale(t, t);
		t *= 1.00001;
		window.display();
	}

	return 0;
}*/