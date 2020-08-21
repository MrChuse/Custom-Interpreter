#include "field.h"
#include <iostream>

Field::Field(int width, int height, int seed) {
	this->width = width;
	this->height = height;
	this->seed = seed;

	share_penalty = 0.75;
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

void Field::spawn_agent(Agent* agent, int x, int y) {
	if (xy_outside_borders(x, y))
		return;
	agent->x = x;
	agent->y = y;
	field[x][y].agent = agent;
	queue.push_back(agent);
}

int Field::kill_agent(int x, int y) {
	int recieved_energy = field[x][y].agent->energy;
	field[x][y].agent = nullptr;
	field[x][y].add_meat(recieved_energy);
	return recieved_energy;
}

void Field::move_agent(Agent* agent, int x, int y) {
	if (xy_outside_borders(x, y) || !agent->xy_in_radius(x, y) || field[x][y].is_occupied())
		return;
	int amt = (agent->x - x) * (agent->x - x) + (agent->y - y) * (agent->y - y);

	agent->energy -= 4 * amt;

	//std::cout << agent->x << agent->y << std::endl << field[agent->x][agent->y].agent << std::endl;
	field[agent->x][agent->y].agent = nullptr;
	agent->x = x;
	agent->y = y;
	field[x][y].agent = agent;
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

void Field::give_birth_to(Agent* agent, int x, int y, int energy, float change_radius_probability, float change_energy_max_probability, float mutate_brain_probability,
		int number_of_brain_changes, float change_gene_probability, float change_brain_size_probability, int max_brain_size_change) {
	if (agent->energy < energy || xy_outside_borders(x, y) || !agent->xy_in_radius(x, y))
		return;
	if (field[x][y].is_occupied()) {
		kill_agent(agent->x, agent->y);
		return;
	}
	agent->energy -= energy;
	Interpreter a = agent->get_brain();
	Interpreter b(a.get_memory(), a.get_commands(), a.get_max_value(), a.get_limit());
	field[x][y].agent = new Agent(x, y, agent->get_radius(), energy, agent->get_energy_max(), b);
	field[x][y].agent->mutate(change_radius_probability, change_energy_max_probability, mutate_brain_probability, number_of_brain_changes, change_gene_probability, change_brain_size_probability, max_brain_size_change);
}

void Field::give_birth_random(Agent* agent, float change_radius_probability, float change_energy_max_probability, float mutate_brain_probability,
		int number_of_brain_changes, float change_gene_probability, float change_brain_size_probability, int max_brain_size_change) {
	int dx = int(agent->random() * (2 * agent->get_radius() + 1));
	int dy = int(agent->random() * (2 * agent->get_radius() + 1));
	int energy = agent->energy / 2;
	give_birth_to(agent, agent->x + dx, agent->y + dy, energy, change_radius_probability, change_energy_max_probability, mutate_brain_probability,
		number_of_brain_changes, change_gene_probability, change_brain_size_probability, max_brain_size_change);
}

void Field::share_energy(Agent* agent, int x, int y, int amount) {
	if (agent->energy < amount || xy_outside_borders(x, y) || agent->xy_in_radius(x, y))
		return;
	agent->energy -= amount;
	field[x][y].agent->energy += amount * share_penalty;
}

void do_nothing(Agent* agent) {
	return;
}

void Field::temperature_effect(Agent* agent) {
	agent->energy -= field[agent->x][agent->y].get_temperature() / 10;
}

void Field::brain_size_effect(Agent* agent) {
	int size = agent->get_brain().get_size();
	agent->energy -= (size > 64) ? (sqrt(size) / 2) : ((size - 64) * (size - 64) / 5 + 4);
}

dx_dy Field::from_position_to_dx_dy(int position, int radius) {
	position %= (2 * radius + 1) * (2 * radius + 1);

	dx_dy ans;

	if (position == 0) {
		ans.dx = 0;
		ans.dy = 0;
		return ans;
	}
	int cycle = 0;
	for (int i = 0; i <= radius; i++) {
		if (position >= (2 * i + 1) * (2 * i + 1)) {
			continue;
		}
		cycle = i;
		break;
	}

	int d = (position - (2 * cycle - 1) * (2 * cycle - 1)) / 4;
	if (position % 4 == 1) { // up
		ans.dx = -cycle + d;
		ans.dy = -cycle;
		return ans;
	}
	if (position % 4 == 2) { // right
		ans.dx = cycle;
		ans.dy = -cycle + d;
		return ans;
	}
	if (position % 4 == 3) { // down
		ans.dx = cycle - d;
		ans.dy = cycle;
		return ans;
	}
	ans.dx = -cycle; // left
	ans.dy = cycle - d;
	return ans;
}

void Field::update() {
	spawn_minerals();
	for (int agent_id = 0; agent_id < queue.size(); agent_id++) {
		Agent* agent = queue[agent_id];
		if (field[agent->x][agent->y].agent == nullptr) {
			delete agent;
			queue.erase(queue.begin() + agent_id);
		}
		std::vector<int> commands_and_arguments = agent->get_brain().make_a_move(SensorData());// get_sensor_data(agent));

		if (commands_and_arguments[0] == 1) {
			photosynthesis(agent);
		}
		else if (commands_and_arguments[0] == 2) {
			dx_dy xy = from_position_to_dx_dy(commands_and_arguments[1], agent->get_radius());
			move_agent(agent, agent->x + xy.dx, agent->y + xy.dy);
		}
		else if (commands_and_arguments[0] == 3) {
			dx_dy xy = from_position_to_dx_dy(commands_and_arguments[1], agent->get_radius());
			eat_meat(agent, agent->x + xy.dx, agent->y + xy.dy);
		}
		else if (commands_and_arguments[0] == 4) {
			dx_dy xy = from_position_to_dx_dy(commands_and_arguments[1], agent->get_radius());
			eat_minerals(agent, agent->x + xy.dx, agent->y + xy.dy);
		}
		else if (commands_and_arguments[0] == 5) {
			dx_dy xy = from_position_to_dx_dy(commands_and_arguments[1], agent->get_radius());
			hit_agent(agent, agent->x + xy.dx, agent->y + xy.dy);
		}
		else if (commands_and_arguments[0] == 6) {
			dx_dy xy = from_position_to_dx_dy(commands_and_arguments[1], agent->get_radius());
			give_birth_to(agent, agent->x + xy.dx, agent->y + xy.dy, commands_and_arguments[2],
						  0, 0, 0, 0, 0, 0, 0);
		}
		else if (commands_and_arguments[0] == 7) {
			dx_dy xy = from_position_to_dx_dy(commands_and_arguments[1], agent->get_radius());
			share_energy(agent, agent->x + xy.dx, agent->y + xy.dy, commands_and_arguments[2]);
		}
		temperature_effect(agent);
		brain_size_effect(agent);

		// check if it died
		if (agent->energy < agent->get_energy_min()) {
			kill_agent(agent->x, agent->y);
		}
		if (agent->energy > agent->get_energy_max()) {
			give_birth_random(agent, 0, 0, 0, 0, 0, 0, 0);
		}
		
	}
}