#include "Wall.h"
#include "Map.h"

Wall::Wall(Map& map, int position_x, int position_y) : map_(map), sf::RectangleShape(sf::Vector2f(map_.SquareSize(), map_.SquareSize())) {
    setPosition(position_x * map_.SquareSize(), position_y * map_.SquareSize());
    setFillColor(sf::Color::Blue);
}