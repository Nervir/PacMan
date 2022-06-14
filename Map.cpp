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
}

void Map::DrawItems() {
    for (auto star : stars_) {
        window_.draw(star);
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
    if (player_.getGlobalBounds().intersects(npc_.getGlobalBounds())) {
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
        auto elapsed = clock_.restart();
        Animate(elapsed);
        DrawWalls();
        DrawItems();
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
    if (PlayerGetItem(player_.getGlobalBounds())) { 
        player_.ScoreUp(); 
        sound_.setBuffer(coin_sound_);
        sound_.play();
    }
}

const std::vector<std::vector<bool>>& Map::ReturnYXMap() {
    return y_x_map_;
}

bool Map::PlayerGetItem(sf::Rect<float> player_bounds) {
    for (int i = 0; i < stars_.size(); i++) {
        if (player_bounds.intersects(stars_[i].getGlobalBounds())) {
            stars_.erase(stars_.begin() + i);
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