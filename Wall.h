#pragma once
#include <SFML/Graphics.hpp>
#include <Map.h>

class Wall : public sf::RectangleShape {
public:
    Wall(Map& map, int position_x, int position_y);
private:
    Map& map_;
};