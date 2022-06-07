#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <Wall.h>
#include <Item.h>
#include <Player.h>
#include <NPC.h>

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
    std::vector<Item> ReturnItems();
    bool PlayerGetItem(sf::Rect<float> player_bounds);
private:
    float square_size_ = 20.f;
    std::vector<std::vector<bool>> y_x_map_;
    std::vector<Wall> walls_;
    sf::RenderWindow& window_;
    std::vector<Item> items_;
    Player player_;
    NPC npc_;
    sf::Clock clock_;
};