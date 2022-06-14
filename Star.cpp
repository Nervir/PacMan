#include "Star.h"

Star::Star(Map& map, int position_x, int position_y) : Item(map, position_x, position_y) {
	setFillColor(sf::Color::Yellow);
}