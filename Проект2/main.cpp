#include "custom_interpreter.h"
#include "field.h"
#include <iostream>

int test_interpreter(std::vector<int> memory, std::vector<std::vector<int>> correct, int id) {
	std::cout << id << std::endl;
	Command photosynthesis(0, true, nullptr);
	Command eat(1, true, nullptr);
	Command com10(10, true, nullptr);

	std::vector<Command> commands = { photosynthesis, eat, com10 };
	std::vector<Cell*> data;

	Interpreter brain(memory, commands, 64, 10);
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

int test_agent_spawn_photo_move(int id) {
	std::cout << id << std::endl;
	Field f = Field(10, 10, 100);

	Command do_nothing(0, true);
	Command photosynthesis(0, true);
	Command eat(1, true);
	Command com10(10, true);

	std::vector<Command> commands = { do_nothing, photosynthesis, eat, com10 };
	std::vector<int> memory = { 0 };
	Interpreter b(memory, commands, 64, 10);
	auto a = new Agent(0, 4, 1, 100, 256, b);
	f.spawn_agent(a, 0, 4);
	auto v = f.get_field();

	f.photosynthesis(a);
	if (a->energy != 164) {
		std::cout << "Energy after photosythesis is not 164, it is " << a->energy << std::endl;
		return -1;
	}

	f.move_agent(a, 0, 6);
	v = f.get_field();
	if (a->x != 0 || a->y != 4) {
		std::cout << "after illegally moving the agent, he really moved to " << a->x << ", " << a->y << std::endl;
		//return -1;
	}
	if (v[0][6].agent != nullptr || (v[0][4].agent != a)) {
		std::cout << "there's something wring with pointers after illegal move" << std::endl;
		//return -1;
	}


	f.move_agent(a, 0, 5);
	v = f.get_field();
	if (a->x != 0 || a->y != 5) {
		std::cout << "after legally moving the agent, he didn't really moved and stayed at " << a->x << ", " << a->y << std::endl;
		return -1;
	}
	if (v[0][5].agent != a || (v[0][4].agent != nullptr)) {
		std::cout << "there's something wring with pointers after legal move" << std::endl << a << " a, " << v[0][4].agent<< " 4th cell, " << v[0][5].agent << " 5th cell." << std::endl;
		return -1;
	}
	delete a;
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

	test_agents_empty(2);

	test_agent_spawn_photo_move(3);

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