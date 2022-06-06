#pragma once
#include <SFML/Graphics.hpp>

class Map;

class Item : public sf::CircleShape {
public:
    Item(Map& map, int position_x, int position_y);
private:
    Map *map_;
};