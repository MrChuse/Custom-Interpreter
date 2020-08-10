#ifndef AGENT
#define AGENT

#include "custom_interpreter.h"

class AgentMutationSettings : MutationSettings {
public:
	float prob1, prob2;
};

class Agent {
public:
	int x;
	int y;
	int energy = 0;

	Agent(int x, int y, int radius, int energy, int energy_cap, Brain* brain) : x(x), y(y), radius(radius), energy(energy), energy_cap(energy_cap), brain(brain) {}

	void mutate(MutationSettings* settings) {
		if (0 < settings->prob1) {

		}
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

/*
�, �������, ��� � �� �����, ��� �������� ������������ ���������, ��������

��� ���� � ���� ���� ����� � ��� ����� ������;
���� ����� �, ������� ��� ��������� � � �������� ���� ���� int c;

� ��� �� �������, ������� ����� � ���������� �* � - ������ �� ������ ������ � - ��� ����� �������� �
� ���� �������� ���������� ������ �� ������ ������ �
��, ��������, �->c �� ��������, ��� ��� � �� �������� ������ ����


*/