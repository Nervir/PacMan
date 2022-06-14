#include "SpeedBoost.h"

SpeedBoost::SpeedBoost(Map& map, int position_x, int position_y) : Item(map, position_x, position_y) {
	setFillColor(sf::Color::Cyan);
}