#include "NPC.h"
#include "Map.h"

NPC::NPC(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 2) {
    setPosition(position_x * map_.SquareSize(), position_y * map_.SquareSize());
    setFillColor(sf::Color::Red);
}

void NPC::animate(const sf::Time& elapsed) {
    if (last_direction_ == 0) {
        srand((unsigned)time(0));
        last_direction_ = 1 + (rand() % 4);
    }
    if (last_direction_ == 1) {
        move(speed_ * elapsed.asSeconds(), 0.f);
        //get his bounding box
        auto bounding_box = getGlobalBounds();
        //check if it overlaps with a wall
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                //if so, move him back same amount
                move(-speed_ * elapsed.asSeconds(), 0.f);
                last_direction_ = 0;
                break;
            }
        }
    }
    if (last_direction_ == 2) {
        move(-speed_ * elapsed.asSeconds(), 0.f);
        auto bounding_box = getGlobalBounds();
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(speed_ * elapsed.asSeconds(), 0.f);
                last_direction_ = 0;
                break;
            }
        }
    }
    if (last_direction_ == 3) {
        move(0.f, speed_ * elapsed.asSeconds());
        auto bounding_box = getGlobalBounds();
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(0.f, -speed_ * elapsed.asSeconds());
                last_direction_ = 0;
                break;
            }
        }
    }
    if (last_direction_ == 4) {
        move(0.f, -speed_ * elapsed.asSeconds());
        auto bounding_box = getGlobalBounds();
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(0.f, speed_ * elapsed.asSeconds());
                last_direction_ = 0;
                break;
            }
        }
    }
}