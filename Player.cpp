#include "Player.h"
#include "Map.h"
#include <iostream>

Player::Player(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 2), position_x_(position_x), position_y_(position_y) {
    setPosition(position_x_ * map_.SquareSize(), position_y_ * map_.SquareSize());
    setFillColor(sf::Color::Green);
}

void Player::animate(const sf::Time& elapsed) {

    //update player position in relation to y_x_map_ if it's on a square
    if (EvenPosition()) {
        position_x_ = static_cast<int>(getPosition().x / map_.SquareSize());
        position_y_ = static_cast<int>(getPosition().y / map_.SquareSize());
    }

    //update last pressed key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) new_direction_ = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) new_direction_ = 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) new_direction_ = 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) new_direction_ = 4;

    //check if I can change direction
    if (EvenPosition() && new_direction_ == 1) {
        if (map_.ReturnYXMap()[position_y_][position_x_ + 1] == true) {
            old_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }

    if (EvenPosition() && new_direction_ == 2) {
        if (map_.ReturnYXMap()[position_y_][position_x_ - 1] == true) {
            old_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }

    if (EvenPosition() && new_direction_ == 3) {
        if (map_.ReturnYXMap()[position_y_ + 1][position_x_] == true) {
            old_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }

    if (EvenPosition() && new_direction_ == 4) {
        if (map_.ReturnYXMap()[position_y_ - 1][position_x_] == true) {
            old_direction_ = new_direction_;
            new_direction_ = 0;
        }
    }

    //Check if old_direction is viable
    if (old_direction_ == 1 && map_.ReturnYXMap()[position_y_][position_x_ + 1] == false) {
         old_direction_ = 0;
    }

    if (old_direction_ == 2 && map_.ReturnYXMap()[position_y_][position_x_ - 1] == false) {
        old_direction_ = 0;
    }

    if (old_direction_ == 3 && map_.ReturnYXMap()[position_y_ + 1][position_x_] == false) {
        old_direction_ = 0;
    }

    if (old_direction_ == 4 && map_.ReturnYXMap()[position_y_ - 1][position_x_] == false) {
        old_direction_ = 0;
    }

    //Move in old_direction
    float percent = 1.1f;

    if (old_direction_ == 1) {
        if (getPosition().x > ((position_x_ + 1) * map_.SquareSize()) - (percent * speed_ * elapsed.asSeconds())) {
            setPosition((position_x_ + 1) * map_.SquareSize(), position_y_ * map_.SquareSize());
        }
        else {
            move(speed_ * elapsed.asSeconds(), 0.f);
        }
    }

    if (old_direction_ == 2) {
        if (getPosition().x < ((position_x_ - 1) * map_.SquareSize()) + (percent * speed_ * elapsed.asSeconds())) {
            setPosition((position_x_ - 1) * map_.SquareSize(), position_y_ * map_.SquareSize());
        }
        else {
            move(-speed_ * elapsed.asSeconds(), 0.f);
        }
    }

    if (old_direction_ == 3) {
        if (getPosition().y > ((position_y_ + 1) * map_.SquareSize()) - (percent * speed_ * elapsed.asSeconds())) {
            setPosition(position_x_ * map_.SquareSize(), (position_y_ + 1) * map_.SquareSize());
        }
        else {
            move(0.f, speed_ * elapsed.asSeconds());
        }
    }

    if (old_direction_ == 4) {
        if (getPosition().y < ((position_y_ - 1) * map_.SquareSize()) + (percent * speed_ * elapsed.asSeconds())) {
            setPosition(position_x_ * map_.SquareSize(), (position_y_ - 1) * map_.SquareSize());
        }
        else {
            move(0.f, -speed_ * elapsed.asSeconds());
        }
    }
}

void Player::ScoreUp() {
    score_ += 1;
}

int Player::ReturnScore() {
    return score_;
}

bool Player::EvenPosition() {
    if (getPosition().x == static_cast<int>(getPosition().x) &&
        getPosition().y == static_cast<int>(getPosition().y) &&
        static_cast<int>(getPosition().x) % static_cast<int>(map_.SquareSize()) == 0 &&
        static_cast<int>(getPosition().y) % static_cast<int>(map_.SquareSize()) == 0) {
        return true;
    }
    return false;
}

int Player::ReturnPosition(char xy) {
    if (xy == 'x') {
        return position_x_;
    }
    else if (xy == 'y') {
        return position_y_;
    }
    return -1;
}