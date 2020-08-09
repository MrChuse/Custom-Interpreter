#ifndef AGENT
#define AGENT

#include "custom_interpreter.h"

class Agent {
public:
	int x;
	int y;
	int energy = 0;
	Agent(int x, int y, int energy, int energy_cap, Brain* brain) : x(x), y(y), energy(energy), energy_cap(energy_cap), brain(brain){

	}

	int get_radius() { return radius; }

	bool xy_in_radius(int x1, int y1) {
		return x - x1 >= -radius || x - x1 <= radius || y - y1 >= -radius || y - y1 <= radius;
	}
private:
	int radius;
	int energy_cap;
	Brain* brain;
};

#endif