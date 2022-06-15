#include "Map.h"

#include "MyFont.h"
#include <iostream>

Map::Map(sf::RenderWindow& window) : window_(window), player_(*this, 1, 1), npc_(*this, 8, 8) {
    //read the map from a flie
    std::ifstream infile("Map1.txt");
    std::string line;
    int i = 0;
    while (std::getline(infile, line))
    {
        y_x_map_.resize(y_x_map_.size() + 1);
        for (auto a : line) {
            if (a == '0') {
                y_x_map_[i].push_back(false); //false means the spot is occupied
                walls_.push_back(Wall(*this, int(y_x_map_[i].size()) - 1, int(y_x_map_.size()) - 1)); //create a wall in the coordinates of the spot
            }
            else if (a == '1') {
                y_x_map_[i].push_back(true); //true means the spot it free
                stars_.push_back(Star(*this, int(y_x_map_[i].size()) - 1, int(y_x_map_.size()) - 1)); //creat an item in the coordinates of the spot
            }
        }
        i++;
    }
    if (!coin_sound_.loadFromFile("game-treasure-coin.wav")) {
        std::cout << "Couldn't load coin sound" << std::endl;
    }
    //window_.setSize(sf::Vector2u(y_x_map_[0].size() * square_size_, (y_x_map_.size() + 1) * square_size_));
}

void Map::DrawItems() {
    for (auto star : stars_) {
        window_.draw(star);
    }
    for (auto speed_boost : speed_boosts_) {
        window_.draw(speed_boost);
    }
    for (auto npc_eater : npc_eaters_) {
        window_.draw(npc_eater);
    }
}

float Map::SquareSize() {
    return 20.f;
}

void Map::DrawWalls() {
    for (auto wall : walls_) {
        window_.draw(wall);
    }
}

void Map::DrawPlayer() {
    window_.draw(player_);
}

void Map::DrawNPC() {
    window_.draw(npc_);
}

void Map::Draw() {
    if (player_.getGlobalBounds().intersects(npc_.getGlobalBounds()) && player_.ReturnCanEatNPC()) {
        MyFont game_over(window_);
        std::string text1 = "You Won!";
        sf::Text text = game_over.GameOverFont(text1);
        window_.draw(text);
    }
    else if (player_.getGlobalBounds().intersects(npc_.getGlobalBounds())) {
        MyFont game_over(window_);
        std::string text1 = "Game Over";
        sf::Text text = game_over.GameOverFont(text1);
        window_.draw(text);
    }
    else if (stars_.size() == 0) {
        MyFont game_over(window_);
        std::string text1 = "You Won!";
        sf::Text text = game_over.GameOverFont(text1);
        window_.draw(text);
    }
    else {
        Create_Random_Items();
        DrawItems();
        auto elapsed = clock_animated_.restart();
        Animate(elapsed);
        DrawWalls();
        DrawPlayer();
        DrawNPC();
        MyFont score(window_);
        sf::Text text = score.Score(player_.ReturnScore(), SquareSize());
        window_.draw(text);
    }

}

void Map::Animate(const sf::Time& elapsed) {
    player_.animate(elapsed);
    npc_.FollowPlayer(elapsed, player_.ReturnPosition('x'), player_.ReturnPosition('y'));
    if (PlayerGetStar(player_.getGlobalBounds())) { 
        player_.ScoreUp(); 
        sound_.setBuffer(coin_sound_);
        sound_.play();
    }
    if (PlayerGetSpeedBoost(player_.getGlobalBounds())) {
        player_.SpeedBoost();
    }
    if (PlayerGetNPCEater(player_.getGlobalBounds())) {
        player_.ChangeCanEatNPC(true);
    }
}

const std::vector<std::vector<bool>>& Map::ReturnYXMap() {
    return y_x_map_;
}

bool Map::PlayerGetStar(sf::Rect<float> player_bounds) {
    for (int i = 0; i < stars_.size(); i++) {
        if (player_bounds.intersects(stars_[i].getGlobalBounds())) {
            stars_.erase(stars_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Map::PlayerGetSpeedBoost(sf::Rect<float> player_bounds) {
    for (int i = 0; i < speed_boosts_.size(); i++) {
        if (player_bounds.intersects(speed_boosts_[i].getGlobalBounds())) {
            speed_boosts_.erase(speed_boosts_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Map::PlayerGetNPCEater(sf::Rect<float> player_bounds) {
    for (int i = 0; i < npc_eaters_.size(); i++) {
        if (player_bounds.intersects(npc_eaters_[i].getGlobalBounds())) {
            npc_eaters_.erase(npc_eaters_.begin() + i);
            return true;
        }
    }
    return false;
}

std::vector<Wall> Map::ReturnWalls() {
    return walls_;
}

std::vector<Star> Map::ReturnStars() {
    return stars_;
}

void Map::Create_Random_Items() {
    const sf::Time& elapsed = clock_random_items_.getElapsedTime();
    if (elapsed.asSeconds() > 5) {
        std::vector<std::tuple<int, int>> possible_map_slots;
        for (int y = 0; y < y_x_map_.size(); y++) {
            for (int x = 0; x < y_x_map_[y].size(); x++) {
                if (y_x_map_[y][x]) {
                    possible_map_slots.push_back(std::make_tuple(y, x));
                }
            }
        }
        auto item_slot = possible_map_slots[rand() % possible_map_slots.size()];
        if (rand() % 2) {
            speed_boosts_.push_back(SpeedBoost(*this, std::get<1>(item_slot), std::get<0>(item_slot)));
        }
        else {
            npc_eaters_.push_back(NPCEater(*this, std::get<1>(item_slot), std::get<0>(item_slot)));
        }
        clock_random_items_.restart();
    }
}