#ifndef FIELD
#define FIELD

#include <vector>
#include "cell.h"

struct dx_dy {
	int dx, dy;
};

class Field {
public:
	Field(int width, int height, int seed);

	void update();

	std::vector<std::vector<Cell>> get_field();

	int from_noise_to_temperature(float n);

	void spawn_minerals();

	void spawn_agent(Agent* agent, int x, int y);

	int kill_agent(int x, int y);

	void move_agent(Agent* agent, int x, int y);
	
	void photosynthesis(Agent* agent);

	void eat_meat(Agent* agent, int x, int y);

	void eat_minerals(Agent* agent, int x, int y);

	void hit_agent(Agent* agent, int x, int y);

	Cell* get_info(Agent* agent, int x, int y);

	std::vector<Cell*> get_sensor_data(Agent* agent);

	void give_birth_to(Agent* agent, int x, int y, int energy, float change_radius_probability, float change_energy_max_probability, float mutate_brain_probability,
		int number_of_brain_changes, float change_gene_probability, float change_brain_size_probability, int max_brain_size_change);

	void give_birth_random(Agent* agent, float change_radius_probability, float change_energy_max_probability, float mutate_brain_probability,
		int number_of_brain_changes, float change_gene_probability, float change_brain_size_probability, int max_brain_size_change);

	void share_energy(Agent* agent, int x, int y, int amount);
	
	void do_nothing(Agent* agent);



private:
	int width;
	int height;
	std::vector<std::vector<Cell>> field;
	std::vector<Agent*> queue;

	int seed;
	float mineral_spawn_probability;
	float share_penalty;

	void temperature_effect(Agent* agent);
	void brain_size_effect(Agent* agent);
	bool xy_outside_borders(int x, int y);
	dx_dy from_position_to_dx_dy(int position, int radius);
};

#endif