#pragma once
#include <SFML/Graphics.hpp>

class Map;

class Player : public sf::CircleShape {
public:
    Player(Map& map, int position_x, int position_y);
    void animate(const sf::Time& time);
    void ScoreUp();
    int ReturnScore();
    bool EvenPosition();
    void SpeedBoost();
    int ReturnPosition(char xy);
    bool ReturnCanEatNPC();
    void ChangeCanEatNPC(bool can_eat_npc);
private:
    int position_x_;
    int position_y_;
    Map& map_;
    float speed_ = 100.f;
    int score_ = 0;
    int old_direction_ = 0;
    int new_direction_ = 0;
    bool can_eat_npc_ = false;
};