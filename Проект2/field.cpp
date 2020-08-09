#include "field.h"


Field::Field(int width, int height, int seed) {
	this->width = width;
	this->height = height;
	this->seed = seed;

	field = std::vector<std::vector<Cell>>();
	field.reserve(height);
	for (int i = 0; i < height; i++) {
		std::vector<Cell> row = std::vector<Cell>();
		row.reserve(width);
		for (int j = 0; j < width; j++) {
			int temp = i * 64 / height;
			row.push_back(Cell(temp));
		}
		field.push_back(row);
	}
}

bool Field::xy_outside_borders(int x, int y) {
	return x < 0 || x >= width || y < 0 || y >= height;
}

std::vector<std::vector<Cell>> Field::get_field() {
	return field;
}

void Field::spawn_minerals() {
	for (int i = height / 2 - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			field[i + height / 2][j].add_minerals(i);
		}
	}
}

int Field::kill_agent(int x, int y) {
	int recieved_energy = field[x][y].agent->energy;
	delete field[x][y].agent;
	field[x][y].agent = nullptr;
	field[x][y].add_meat(recieved_energy);
	return recieved_energy;
}

void Field::move_agent(Agent* agent, int x, int y) {
	if (xy_outside_borders(x, y) || !agent->xy_in_radius(x, y) || field[x][y].is_occupied())
		return;

	int amt = (agent->x - x) * (agent->x - x) + (agent->y - y) * (agent->y - y);

	agent->energy -= 4 * amt;

}

void Field::photosynthesis(Agent* agent) {
	agent->energy += field[agent->x][agent->y].photosynthesis();
}

void Field::eat_meat(Agent* agent, int x, int y) {
	if (xy_outside_borders(x, y) || !agent->xy_in_radius(x, y) || !field[x][y].get_meat())
		return;
	agent->energy += field[x][y].eat_meat();
}

void Field::eat_minerals(Agent* agent, int x, int y) {
	if (xy_outside_borders(x, y) || !agent->xy_in_radius(x, y))
		return;
	agent->energy += field[x][y].eat_minerals();
}

void Field::hit_agent(Agent* agent, int x, int y) {
	if (xy_outside_borders(x, y) || !agent->xy_in_radius(x, y))
		return;
	agent->energy -= 4;
	kill_agent(x, y);
}

Cell* Field::get_info(Agent* agent, int x, int y) {
	if (xy_outside_borders(x, y) || !agent->xy_in_radius(x, y))
		return nullptr;
	return &field[x][y];
}

std::vector<Cell*> Field::get_sensor_data(Agent* agent) {
	std::vector<Cell*> sensor_data = { get_info(agent, agent->x, agent->y) };
	for (int r = 1; r <= agent->get_radius(); r++) {
		for (int d = 0; d < 2 * r; d++) {
			std::vector<std::vector<int>> didj = { {-r + d, -r} , {r, -r + d}, {r - d, r}, {-r, r - d} };
			for (int side = 0; side < 4; side++) {
				sensor_data.push_back(get_info(agent, agent->x + didj[side][0], agent->y + didj[side][1]));
			}
		}
	}
	return sensor_data;
}