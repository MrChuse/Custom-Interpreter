#ifndef CELL
#define CELL

#include <algorithm>
#include "agent.h"

class Cell {
public:
	Agent* agent;

	Cell(int temperature, Agent* agent = nullptr) {
		this->temperature = temperature;
		this->agent = agent;

		meat = 0;
		minerals = 0;
		photosyn_energy_value = 64 - (temperature - 1) / 8;
		meat_energy_value = 7 - (temperature - 1) / 8;
		mineral_energy_value = 1;
	}

	bool is_occupied() { return agent != nullptr; }

	bool is_food_here() { return meat + minerals; }

	Agent* get_agent() { return agent; }

	int get_temperature() { return temperature; }

	int get_meat() { return meat; }

	int get_minerals() { return minerals; }

	void add_meat(int energy_amt) { meat = std::min(meat + energy_amt/meat_energy_value/2, 128); }

	void add_minerals(int amt) { minerals = std::min(minerals + amt, 128); }

	int photosynthesis() { return photosyn_energy_value; }

	int eat_meat() {
		if (get_meat()) {
			meat--;
			return meat_energy_value;
		}
		return 0;
	}

	int eat_minerals() {
		int amt = minerals;
		minerals = 0;
		return amt;
	}

private:
	int temperature;

	int meat;
	int minerals;
	int photosyn_energy_value;
	int meat_energy_value;
	int mineral_energy_value;
};

#endif