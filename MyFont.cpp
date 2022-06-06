#include "MyFont.h"
#include <iostream>

MyFont::MyFont(sf::RenderWindow& window) : window_(window) {
    if (!font_.loadFromFile("osaka-re.ttf")) {
        std::cout << "Could not load font." << std::endl;
    }
}

sf::Text MyFont::GameOverFont(std::string input_text) {
    sf::Text text;
    text.setFont(font_);
    text.setString(input_text);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    auto text_bounds = text.getLocalBounds();
    auto window_size = window_.getSize();
    text.setPosition((window_size.x - text_bounds.width) / 2, (window_size.y - (text_bounds.height + text_bounds.top)) / 2);
    return text;
}

sf::Text MyFont::Score(int score, float square_size) {
    sf::Text text;
    text.setFont(font_);
    text.setString("Score: " + std::to_string(score));
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    auto text_bounds = text.getLocalBounds();
    auto window_size = window_.getSize();
    text.setPosition(20, window_size.y - square_size + 2.5f);
    return text;
}