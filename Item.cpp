#include "Item.h"

Item::Item(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 12) {
    setPosition(position_x * map_.SquareSize() + map_.SquareSize() / 2, position_y * map_.SquareSize() + map_.SquareSize() / 2);
    setFillColor(sf::Color::Yellow);
}