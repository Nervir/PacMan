#pragma once
#include <SFML/Graphics.hpp>

class MyFont
{
public:
    MyFont(sf::RenderWindow& window);
    sf::Text GameOverFont(std::string input_text);
    sf::Text Score(int score, float square_size);
private:
    std::string font_file = "osaka-re.ttf";
    sf::Font font_;
    sf::RenderWindow& window_;
};