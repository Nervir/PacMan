#pragma once
#include <SFML/Graphics.hpp>

class Map;

class NPC : public sf::CircleShape {
public:
    NPC(Map& map, int position_x, int position_y);
    void animate(const sf::Time& elapsed);
    void FollowPlayer(const sf::Time& elapsed, int player_position_x, int player_position_y);
    bool EvenPosition();
private:
    int position_x_;
    int position_y_;
    Map& map_;
    float speed_ = 100.f;
    int new_direction_ = 0;
    int old_direction_ = 0;
};