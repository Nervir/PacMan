#include "Player.h"
#include "Map.h"

Player::Player(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 2) {
    setPosition(position_x * map_.SquareSize(), position_y * map_.SquareSize());
    setFillColor(sf::Color::Green);
}

void Player::animate(const sf::Time& time) {
    //check if a key is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || new_direction_ == 1) {
        new_direction_ = 1;
        //move the player
        move(speed_ * time.asSeconds(), 0.f);
        //get his bounding box
        auto bounding_box = getGlobalBounds();
        bool valid_direction = true;
        //check if it overlaps with a wall
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                //if so, move him back same amount
                move(-speed_ * time.asSeconds(), 0.f);
                valid_direction = false;
                break;
            }
        }
        if (valid_direction) {
            move(-speed_ * time.asSeconds(), 0.f);
            last_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || new_direction_ == 2) {
        new_direction_ = 2;
        move(-speed_ * time.asSeconds(), 0.f);
        auto bounding_box = getGlobalBounds();
        bool valid_direction = true;
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(speed_ * time.asSeconds(), 0.f);
                valid_direction = false;
                break;
            }
        }
        if (valid_direction) {
            move(speed_ * time.asSeconds(), 0.f);
            last_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || new_direction_ == 3) {
        new_direction_ = 3;
        move(0.f, speed_ * time.asSeconds());
        auto bounding_box = getGlobalBounds();
        bool valid_direction = true;
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(0.f, -speed_ * time.asSeconds());
                valid_direction = false;
                break;
            }
        }
        if (valid_direction) {
            move(0.f, -speed_ * time.asSeconds());
            last_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || new_direction_ == 4) {
        new_direction_ = 4;
        move(0.f, -speed_ * time.asSeconds());
        auto bounding_box = getGlobalBounds();
        bool valid_direction = true;
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(0.f, speed_ * time.asSeconds());
                valid_direction = false;
                break;
            }
        }
        if (valid_direction) {
            move(0.f, speed_ * time.asSeconds());
            last_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }
    if (last_direction_ == 1) {
        move(speed_ * time.asSeconds(), 0.f);
        //get his bounding box
        auto bounding_box = getGlobalBounds();
        //check if it overlaps with a wall
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                //if so, move him back same amount
                move(-speed_ * time.asSeconds(), 0.f);
                last_direction_ = 0;
                break;
            }
        }
    }
    if (last_direction_ == 2) {
        move(-speed_ * time.asSeconds(), 0.f);
        auto bounding_box = getGlobalBounds();
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(speed_ * time.asSeconds(), 0.f);
                last_direction_ = 0;
                break;
            }
        }
    }
    if (last_direction_ == 3) {
        move(0.f, speed_ * time.asSeconds());
        auto bounding_box = getGlobalBounds();
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(0.f, -speed_ * time.asSeconds());
                last_direction_ = 0;
                break;
            }
        }
    }
    if (last_direction_ == 4) {
        move(0.f, -speed_ * time.asSeconds());
        auto bounding_box = getGlobalBounds();
        for (auto wall : map_.ReturnWalls()) {
            if (bounding_box.intersects(wall.getGlobalBounds())) {
                move(0.f, speed_ * time.asSeconds());
                last_direction_ = 0;
                break;
            }
        }
    }
}

void Player::ScoreUp() {
    score_ += 1;
}

int Player::ReturnScore() {
    return score_;
}