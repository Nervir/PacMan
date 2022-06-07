#include "NPC.h"
#include "Map.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

NPC::NPC(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 2) {
    setPosition(position_x * map_.SquareSize(), position_y * map_.SquareSize());
    setFillColor(sf::Color::Red);
}

void NPC::animate(const sf::Time& elapsed) {

    //update player position in relation to y_x_map_ if it's on a square
    if (EvenPosition()) {
        position_x_ = static_cast<int>(getPosition().x / map_.SquareSize());
        position_y_ = static_cast<int>(getPosition().y / map_.SquareSize());

        //check available directions
        std::vector<int> directions;
        if (map_.ReturnYXMap()[position_y_][position_x_ + 1] == true) {
            directions.push_back(1);
        }
        if (map_.ReturnYXMap()[position_y_][position_x_ - 1] == true) {
            directions.push_back(2);
        }
        if (map_.ReturnYXMap()[position_y_ + 1][position_x_] == true) {
            directions.push_back(3);
        }
        if (map_.ReturnYXMap()[position_y_ - 1][position_x_] == true) {
            directions.push_back(4);
        }

        //if not moving or on at an intersection, roll a random direction from available directions
        if (old_direction_ == 0 || directions.size() > 2) {
            srand(time(NULL));
            int random_number = rand() % directions.size();
            old_direction_ = directions[random_number];
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

void NPC::FollowPlayer(const sf::Time& elapsed, int player_position_x, int player_position_y) {

    //update npc position in relation to y_x_map_ if it's on a square
    if (EvenPosition()) {
        position_x_ = static_cast<int>(getPosition().x / map_.SquareSize());
        position_y_ = static_cast<int>(getPosition().y / map_.SquareSize());

        //check available directions
        std::vector<int> directions;
        if (map_.ReturnYXMap()[position_y_][position_x_ + 1] == true) {
            directions.push_back(1);
        }
        if (map_.ReturnYXMap()[position_y_][position_x_ - 1] == true) {
            directions.push_back(2);
        }
        if (map_.ReturnYXMap()[position_y_ + 1][position_x_] == true) {
            directions.push_back(3);
        }
        if (map_.ReturnYXMap()[position_y_ - 1][position_x_] == true) {
            directions.push_back(4);
        }

        if (position_x_ < player_position_x) {
            if (std::find(directions.begin(), directions.end(), 1) != directions.end()) {
                old_direction_ = 1;
            }
        }

        if (position_x_ > player_position_x) {
            if (std::find(directions.begin(), directions.end(), 2) != directions.end()) {
                old_direction_ = 2;
            }
        }

        if (position_y_ < player_position_y) {
            if (std::find(directions.begin(), directions.end(), 3) != directions.end()) {
                old_direction_ = 3;
            }
        }

        if (position_y_ > player_position_y) {
            if (std::find(directions.begin(), directions.end(), 4) != directions.end()) {
                old_direction_ = 4;
            }
        }
    }

    ////Check if old_direction is viable
    //if (old_direction_ == 1 && map_.ReturnYXMap()[position_y_][position_x_ + 1] == false) {
    //    old_direction_ = 0;
    //}

    //if (old_direction_ == 2 && map_.ReturnYXMap()[position_y_][position_x_ - 1] == false) {
    //    old_direction_ = 0;
    //}

    //if (old_direction_ == 3 && map_.ReturnYXMap()[position_y_ + 1][position_x_] == false) {
    //    old_direction_ = 0;
    //}

    //if (old_direction_ == 4 && map_.ReturnYXMap()[position_y_ - 1][position_x_] == false) {
    //    old_direction_ = 0;
    //}

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

bool NPC::EvenPosition() {
    if (getPosition().x == static_cast<int>(getPosition().x) &&
        getPosition().y == static_cast<int>(getPosition().y) &&
        static_cast<int>(getPosition().x) % static_cast<int>(map_.SquareSize()) == 0 &&
        static_cast<int>(getPosition().y) % static_cast<int>(map_.SquareSize()) == 0) {
        return true;
    }
    return false;
}