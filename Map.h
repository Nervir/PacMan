#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <Wall.h>
#include <Player.h>
#include <NPC.h>
#include <SFML/Audio.hpp>
#include "Star.h"

class Map {
public:
    Map(sf::RenderWindow& window);
    float SquareSize();
    void DrawWalls();
    void DrawItems();
    void DrawPlayer();
    void DrawNPC();
    void Draw();
    void Animate(const sf::Time& elapsed);
    const std::vector<std::vector<bool>>& ReturnYXMap();
    std::vector<Wall> ReturnWalls();
    std::vector<Star> ReturnStars();
    bool PlayerGetItem(sf::Rect<float> player_bounds);
private:
    float square_size_ = 20.f;
    std::vector<std::vector<bool>> y_x_map_;
    std::vector<Wall> walls_;
    sf::RenderWindow& window_;
    std::vector<Star> stars_;
    Player player_;
    NPC npc_;
    sf::Clock clock_;
    sf::SoundBuffer coin_sound_;
    sf::Sound sound_;
};