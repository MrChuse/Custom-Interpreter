#ifndef FIELD
#define FIELD

#include <vector>
#include "cell.h"

class Field {
public:
	Field(int width, int height, int seed);

	std::vector<std::vector<Cell>> get_field();

	int from_noise_to_temperature(float n);

	void spawn_minerals();

	int kill_agent(int x, int y);

	void move_agent(Agent* agent, int x, int y);
	
	void photosynthesis(Agent* agent);

	void eat_meat(Agent* agent, int x, int y);

	void eat_minerals(Agent* agent, int x, int y);

	void hit_agent(Agent* agent, int x, int y);

	Cell* get_info(Agent* agent, int x, int y);

	std::vector<Cell*> get_sensor_data(Agent* agent);

	void give_birth_to(Agent* agent, int x, int y, int energy, int BRAIN_SETTINGS, int MUTATION_SETTINGS);

	void give_birth_random(Agent* agent, int BRAIN_SETTINGS, int MUTATION_SETTINGS);

	void share_energy(Agent* agent, int x, int y, int amount);
	
	void do_nothing(Agent* agent);



private:
	int width;
	int height;
	std::vector<std::vector<Cell>> field;

	int seed;
	float mineral_spawn_probability;
	float share_penalty;

	bool xy_outside_borders(int x, int y);
};

#endif