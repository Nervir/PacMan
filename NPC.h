#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class NPC : public sf::CircleShape {
public:
    NPC(Map& map, int position_x, int position_y);
    void animate(const sf::Time& time);
private:
    Map& map_;
    float speed_ = 50.f;
    int last_direction_ = 0;
    int new_direction_ = 0;
};