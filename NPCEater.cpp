#include "NPCEater.h"

NPCEater::NPCEater(Map& map, int position_x, int position_y) : Item(map, position_x, position_y) {
	setFillColor(sf::Color::Magenta);
}