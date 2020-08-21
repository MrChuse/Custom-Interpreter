/* #ifndef GAME
#define GAME

#include "field.h"

struct dx_dy {
	int dx;
	int dy;
};

class Game {
public:
	Game();

	void update();

private:
	dx_dy from_position_to_dx_dy(int position, int radius);

	Field field;
	int current_tick;
};

#endif
*/