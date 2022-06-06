#pragma once
#include <SFML/Graphics.hpp>

class Map;

class Player : public sf::CircleShape {
public:
    Player(Map& map, int position_x, int position_y);
    void animate(const sf::Time& time);
    void ScoreUp();
    int ReturnScore();
private:
    Map& map_;
    float speed_ = 100.f;
    int score_ = 0;
    int last_direction_ = 0;
    int new_direction_ = 0;
};