#ifndef DRAW
#define DRAW

#include <SFML/Graphics.hpp>
#include "circle.h"

void draw_circle (sf::RenderWindow window, Circle c) {
	sf::CircleShape shape(c.get_radius());
	shape.setFillColor(c.get_color());
	shape.setPosition(c.get_x(), c.get_y());
	window.draw(shape);
}

#endif