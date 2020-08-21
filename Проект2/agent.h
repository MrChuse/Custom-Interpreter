#ifndef AGENT
#define AGENT

#include <cstdlib>
#include "custom_interpreter.h"

/*class AgentMutationSettings : MutationSettings {
public:
	float prob1, prob2;
};
*/

class Agent {
public:
	int x;
	int y;
	int energy;

	Agent(int x, int y, int radius, int energy, int energy_max, Interpreter brain) : x(x), y(y), radius(radius), energy(energy), energy_max(energy_max), brain(brain) {}

	void mutate(float change_radius_probability, float change_energy_max_probability, float mutate_brain_probability, int number_of_brain_changes, float change_gene_probability, float change_brain_size_probability, int max_brain_size_change) {
		if (random() > change_radius_probability)
			if (random() > 0.5)
				radius += 1;
			else
				radius = (1 > radius - 1) ? 1 : radius - 1;
		
		if (random() > change_energy_max_probability) {
			int dmax = int(random() * 33 - 16);
			energy_max = (1.5 * energy_min > energy_max + dmax) ? int(1.5 * energy_min) : energy_max + dmax;
		}
		if (random() > mutate_brain_probability)
			brain.mutate(number_of_brain_changes, change_gene_probability, change_brain_size_probability, max_brain_size_change);
	}
	
	int get_radius() { return radius; }

	int get_energy_max() { return energy_max; }

	int get_energy_min() { return energy_min; }

	Interpreter get_brain() { return brain; }

	bool xy_in_radius(int x1, int y1) const {
		return x - x1 >= -radius && x - x1 <= radius && y - y1 >= -radius && y - y1 <= radius;
	}

	float random() {
		return 1.f * rand() / RAND_MAX;
	}
private:
	int radius;
	static const int energy_min = 64;
	int energy_max;
	Interpreter brain;
};

#endif

/*
�, �������, ��� � �� �����, ��� �������� ������������ ���������, ��������

��� ���� � ���� ���� ����� � ��� ����� ������;
���� ����� �, ������� ��� ��������� � � �������� ���� ���� int c;

� ��� �� �������, ������� ����� � ���������� �* � - ������ �� ������ ������ � - ��� ����� �������� �
� ���� �������� ���������� ������ �� ������ ������ �
��, ��������, �->c �� ��������, ��� ��� � �� �������� ������ ����


*/