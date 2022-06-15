#include "Player.h"
#include "Map.h"
#include <iostream>

Player::Player(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 2), position_x_(position_x), position_y_(position_y) {
    setOrigin(getRadius(), getRadius());
    setPosition(position_x_ * map_.SquareSize() + getRadius(), position_y_ * map_.SquareSize() + getRadius());
    if (!texture0_.loadFromFile("Circle1.png"))
    {
        std::cerr << "failed to load image" << std::endl;
        exit(1);
    }
    setTexture(&texture0_);
    if (!texture1_.loadFromFile("Circle3.png"))
    {
        std::cerr << "failed to load image" << std::endl;
        exit(1);
    }
}

void Player::animate(const sf::Time& elapsed) {

    //animate movement
    if (clock_.getElapsedTime().asSeconds() > 0.25f) {
        if (getTexture() == &texture0_) {
            setTexture(&texture1_);
        }
        else {
            setTexture(&texture0_);
        }
        clock_.restart();
    }

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
        setRotation(0);
        if (getPosition().x > ((position_x_ + 1) * map_.SquareSize() + getRadius()) - (percent * speed_ * elapsed.asSeconds())) {
            setPosition((position_x_ + 1) * map_.SquareSize() + getRadius(), position_y_ * map_.SquareSize() + getRadius());
        }
        else {
            move(speed_ * elapsed.asSeconds(), 0.f);
        }
    }

    if (old_direction_ == 2) {
        setRotation(180);
        if (getPosition().x < ((position_x_ - 1) * map_.SquareSize() + getRadius()) + (percent * speed_ * elapsed.asSeconds())) {
            setPosition((position_x_ - 1) * map_.SquareSize() + getRadius(), position_y_ * map_.SquareSize() + getRadius());
        }
        else {
            move(-speed_ * elapsed.asSeconds(), 0.f);
        }
    }

    if (old_direction_ == 3) {
        setRotation(90);
        if (getPosition().y > ((position_y_ + 1) * map_.SquareSize() + getRadius()) - (percent * speed_ * elapsed.asSeconds())) {
            setPosition(position_x_ * map_.SquareSize() + getRadius(), (position_y_ + 1) * map_.SquareSize() + getRadius());
        }
        else {
            move(0.f, speed_ * elapsed.asSeconds());
        }
    }

    if (old_direction_ == 4) {
        setRotation(270);
        if (getPosition().y < ((position_y_ - 1) * map_.SquareSize() + getRadius()) + (percent * speed_ * elapsed.asSeconds())) {
            setPosition(position_x_ * map_.SquareSize() + getRadius(), (position_y_ - 1) * map_.SquareSize() + getRadius());
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
        static_cast<int>(getPosition().x - getRadius()) % static_cast<int>(map_.SquareSize()) == 0 &&
        static_cast<int>(getPosition().y - getRadius()) % static_cast<int>(map_.SquareSize()) == 0) {
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

void Player::SpeedBoost() {
    speed_ *= 1.1f;
}

bool Player::ReturnCanEatNPC() {
    return can_eat_npc_;
}

void Player::ChangeCanEatNPC(bool can_eat_npc) {
    can_eat_npc_ = can_eat_npc;
}