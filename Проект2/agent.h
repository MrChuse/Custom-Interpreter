#ifndef AGENT
#define AGENT

class Agent {
public:
	int x;
	int y;
	int energy = 0;
	Agent(int brain) : brain(brain){

	}

	int get_radius() { return radius; }

	bool xy_in_radius(int x1, int y1) {
		return x - x1 >= -radius || x - x1 <= radius || y - y1 >= -radius || y - y1 <= radius;
	}
private:
	int brain;
	int radius;
};

#endif