#ifndef BRAIN
#define BRAIN

class SensorData {};

class MutationSettings {};

class Brain {
public:
	virtual std::vector<int> make_a_move(SensorData data) = 0;

	virtual void mutate(MutationSettings settings) = 0;

	virtual bool check_ally(Brain* other) = 0;

	virtual int get_size() = 0;
};

#endif