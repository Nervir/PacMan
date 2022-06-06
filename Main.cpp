#include <SFML/Graphics.hpp>
#include <Wall.h>
#include <Item.h>
#include <Player.h>
#include <NPC.h>
#include <Map.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 220), "SFML works!");
    Map map(window);
    //Player player(map);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        auto elapsed = clock.restart();
        window.clear();
        map.Animate(elapsed);
        map.Draw();
        window.display();
    }

    return 0;
}

//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//
//// forward declare classes
//
//class MyFont;
//class Wall;
//class Map;
//class Player;
//class Item;
//class NPC;
//
//// define member variables and function prototypes for each class
//
//class MyFont
//{
//public:
//    MyFont(sf::RenderWindow& window);
//    sf::Text GameOverFont(std::string input_text);
//    sf::Text Score(int score, float square_size);
//private:
//    std::string font_file = "osaka-re.ttf";
//    sf::Font font_;
//    sf::RenderWindow& window_;
//};
//
//class Wall : public sf::RectangleShape {
//public:
//    Wall(Map& map, int position_x, int position_y);
//private:
//    Map& map_;
//};
//
//class Player : public sf::CircleShape {
//public:
//    Player(Map& map, int position_x, int position_y);
//    void animate(const sf::Time& time);
//    void ScoreUp();
//    int ReturnScore();
//private:
//    Map& map_;
//    float speed_ = 100.f;
//    int score_ = 0;
//    int last_direction_ = 0;
//    int new_direction_ = 0;
//};
//
//class NPC : public sf::CircleShape {
//public:
//    NPC(Map& map, int position_x, int position_y);
//    void animate(const sf::Time& time);
//private:
//    Map& map_;
//    float speed_ = 50.f;
//    int last_direction_ = 0;
//    int new_direction_ = 0;
//};
//
//class Map {
//public:
//    Map(sf::RenderWindow& window);
//    float SquareSize();
//    void DrawWalls();
//    void DrawItems();
//    void DrawPlayer();
//    void DrawNPC();
//    void Draw();
//    void Animate(const sf::Time& elapsed);
//    std::vector<Wall> ReturnWalls();
//    std::vector<Item> ReturnItems();
//    bool PlayerGetItem(sf::Rect<float> player_bounds);
//private:
//    float square_size_ = 20.f;
//    std::vector<std::vector<bool>> y_x_map_;
//    std::vector<Wall> walls_;
//    sf::RenderWindow& window_;
//    std::vector<Item> items_;
//    Player player_;
//    NPC npc_;
//};
//
//class Item : public sf::CircleShape {
//public:
//    Item(Map& map, int position_x, int position_y);
//private:
//    Map& map_;
//};
//
//// implement memeber functions of each class.
//
//MyFont::MyFont(sf::RenderWindow& window) : window_(window) {
//    if (!font_.loadFromFile("osaka-re.ttf")) {
//        std::cout << "Could not load font." << std::endl;
//    }
//}
//
//sf::Text MyFont::GameOverFont(std::string input_text) {
//    sf::Text text;
//    text.setFont(font_);
//    text.setString(input_text);
//    text.setCharacterSize(25);
//    text.setFillColor(sf::Color::Red);
//    text.setStyle(sf::Text::Bold);
//    auto text_bounds = text.getLocalBounds();
//    auto window_size = window_.getSize();
//    text.setPosition((window_size.x - text_bounds.width) / 2, (window_size.y - (text_bounds.height + text_bounds.top)) / 2);
//    return text;
//}
//
//sf::Text MyFont::Score(int score, float square_size) {
//    sf::Text text;
//    text.setFont(font_);
//    text.setString("Score: " + std::to_string(score));
//    text.setCharacterSize(15);
//    text.setFillColor(sf::Color::Red);
//    text.setStyle(sf::Text::Bold);
//    auto text_bounds = text.getLocalBounds();
//    auto window_size = window_.getSize();
//    text.setPosition(20, window_size.y - square_size + 2.5f);
//    return text;
//}
//
//Wall::Wall(Map& map, int position_x, int position_y) : map_(map), sf::RectangleShape(sf::Vector2f(map_.SquareSize(), map_.SquareSize())) {
//    setPosition(position_x * map_.SquareSize(), position_y * map_.SquareSize());
//    setFillColor(sf::Color::Blue);
//}
//
//Map::Map(sf::RenderWindow& window) : window_(window), player_(*this, 1, 1), npc_(*this, 8, 8) {
//    //read the map from a flie
//    std::ifstream infile("Map1.txt");
//    std::string line;
//    int i = 0;
//    while (std::getline(infile, line))
//    {
//        y_x_map_.resize(y_x_map_.size() + 1);
//        for (auto a : line) {
//            if (a == '0') {
//                y_x_map_[i].push_back(false); //false means the spot is occupied
//                walls_.push_back(Wall(*this, int(y_x_map_[i].size()) - 1, int(y_x_map_.size()) - 1)); //create a wall in the coordinates of the spot
//            }
//            else if (a == '1') {
//                y_x_map_[i].push_back(true); //true means the spot it free
//                items_.push_back(Item(*this, int(y_x_map_[i].size()) - 1, int(y_x_map_.size()) - 1)); //creat an item in the coordinates of the spot
//            }
//        }
//        i++;
//    }
//}
//
//void Map::DrawItems() {
//    for (auto item : items_) {
//        window_.draw(item);
//    }
//}
//
//float Map::SquareSize() {
//    return 20.f;
//}
//
//void Map::DrawWalls() {
//    for (auto wall : walls_) {
//        window_.draw(wall);
//    }
//}
//
//void Map::DrawPlayer() {
//    window_.draw(player_);
//}
//
//void Map::DrawNPC() {
//    window_.draw(npc_);
//}
//
//void Map::Draw() {
//    if (player_.getGlobalBounds().intersects(npc_.getGlobalBounds())) {
//        MyFont game_over(window_);
//        std::string text1 = "Game Over";
//        sf::Text text = game_over.GameOverFont(text1);
//        window_.draw(text);
//    }
//    else {
//        DrawWalls();
//        DrawItems();
//        DrawPlayer();
//        DrawNPC();
//        MyFont score(window_);
//        sf::Text text = score.Score(player_.ReturnScore(), SquareSize());
//        window_.draw(text);
//    }
//
//}
//
//void Map::Animate(const sf::Time& elapsed) {
//    player_.animate(elapsed);
//    npc_.animate(elapsed);
//    if (PlayerGetItem(player_.getGlobalBounds())) player_.ScoreUp();
//}
//
//bool Map::PlayerGetItem(sf::Rect<float> player_bounds) {
//    for (int i = 0; i < items_.size(); i++) {
//        if (player_bounds.intersects(items_[i].getGlobalBounds())) {
//            //items_.erase(items_.begin() + i);
//            return true;
//        }
//    }
//    return false;
//}
//
//std::vector<Wall> Map::ReturnWalls() {
//    return walls_;
//}
//
//std::vector<Item> Map::ReturnItems() {
//    return items_;
//}
//
//Player::Player(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 2) {
//    setPosition(position_x * map_.SquareSize(), position_y * map_.SquareSize());
//    setFillColor(sf::Color::Green);
//}
//
//void Player::animate(const sf::Time& time) {
//    //check if a key is pressed
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || new_direction_ == 1) {
//        new_direction_ = 1;
//        //move the player
//        move(speed_ * time.asSeconds(), 0.f);
//        //get his bounding box
//        auto bounding_box = getGlobalBounds();
//        bool valid_direction = true;
//        //check if it overlaps with a wall
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                //if so, move him back same amount
//                move(-speed_ * time.asSeconds(), 0.f);
//                valid_direction = false;
//                break;
//            }
//        }
//        if (valid_direction) {
//            move(-speed_ * time.asSeconds(), 0.f);
//            last_direction_ = new_direction_;
//            new_direction_ = 0;
//        }
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || new_direction_ == 2) {
//        new_direction_ = 2;
//        move(-speed_ * time.asSeconds(), 0.f);
//        auto bounding_box = getGlobalBounds();
//        bool valid_direction = true;
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(speed_ * time.asSeconds(), 0.f);
//                valid_direction = false;
//                break;
//            }
//        }
//        if (valid_direction) {
//            move(speed_ * time.asSeconds(), 0.f);
//            last_direction_ = new_direction_;
//            new_direction_ = 0;
//        }
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || new_direction_ == 3) {
//        new_direction_ = 3;
//        move(0.f, speed_ * time.asSeconds());
//        auto bounding_box = getGlobalBounds();
//        bool valid_direction = true;
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(0.f, -speed_ * time.asSeconds());
//                valid_direction = false;
//                break;
//            }
//        }
//        if (valid_direction) {
//            move(0.f, -speed_ * time.asSeconds());
//            last_direction_ = new_direction_;
//            new_direction_ = 0;
//        }
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || new_direction_ == 4) {
//        new_direction_ = 4;
//        move(0.f, -speed_ * time.asSeconds());
//        auto bounding_box = getGlobalBounds();
//        bool valid_direction = true;
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(0.f, speed_ * time.asSeconds());
//                valid_direction = false;
//                break;
//            }
//        }
//        if (valid_direction) {
//            move(0.f, speed_ * time.asSeconds());
//            last_direction_ = new_direction_;
//            new_direction_ = 0;
//        }
//    }
//    if (last_direction_ == 1) {
//        move(speed_ * time.asSeconds(), 0.f);
//        //get his bounding box
//        auto bounding_box = getGlobalBounds();
//        //check if it overlaps with a wall
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                //if so, move him back same amount
//                move(-speed_ * time.asSeconds(), 0.f);
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//    if (last_direction_ == 2) {
//        move(-speed_ * time.asSeconds(), 0.f);
//        auto bounding_box = getGlobalBounds();
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(speed_ * time.asSeconds(), 0.f);
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//    if (last_direction_ == 3) {
//        move(0.f, speed_ * time.asSeconds());
//        auto bounding_box = getGlobalBounds();
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(0.f, -speed_ * time.asSeconds());
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//    if (last_direction_ == 4) {
//        move(0.f, -speed_ * time.asSeconds());
//        auto bounding_box = getGlobalBounds();
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(0.f, speed_ * time.asSeconds());
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//}
//
//void Player::ScoreUp() {
//    score_ += 1;
//}
//
//int Player::ReturnScore() {
//    return score_;
//}
//
//NPC::NPC(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 2) {
//    setPosition(position_x * map_.SquareSize(), position_y * map_.SquareSize());
//    setFillColor(sf::Color::Red);
//}
//
//void NPC::animate(const sf::Time& elapsed) {
//    if (last_direction_ == 0) {
//        srand((unsigned)time(0));
//        last_direction_ = 1 + (rand() % 4);
//    }
//    //if (new_direction_ == 1) {
//    //    new_direction_ = 1;
//    //    //move the player
//    //    move(speed_ * elapsed.asSeconds(), 0.f);
//    //    //get his bounding box
//    //    auto bounding_box = getGlobalBounds();
//    //    bool valid_direction = true;
//    //    //check if it overlaps with a wall
//    //    for (auto wall : map_.ReturnWalls()) {
//    //        if (bounding_box.intersects(wall.getGlobalBounds())) {
//    //            //if so, move him back same amount
//    //            move(-speed_ * elapsed.asSeconds(), 0.f);
//    //            valid_direction = false;
//    //            break;
//    //        }
//    //    }
//    //    if (valid_direction) {
//    //        move(-speed_ * elapsed.asSeconds(), 0.f);
//    //        last_direction_ = new_direction_;
//    //        new_direction_ = 0;
//    //    }
//    //}
//    //if (new_direction_ == 2) {
//    //    new_direction_ = 2;
//    //    move(-speed_ * elapsed.asSeconds(), 0.f);
//    //    auto bounding_box = getGlobalBounds();
//    //    bool valid_direction = true;
//    //    for (auto wall : map_.ReturnWalls()) {
//    //        if (bounding_box.intersects(wall.getGlobalBounds())) {
//    //            move(speed_ * elapsed.asSeconds(), 0.f);
//    //            valid_direction = false;
//    //            break;
//    //        }
//    //    }
//    //    if (valid_direction) {
//    //        move(speed_ * elapsed.asSeconds(), 0.f);
//    //        last_direction_ = new_direction_;
//    //        new_direction_ = 0;
//    //    }
//    //}
//    //if (new_direction_ == 3) {
//    //    new_direction_ = 3;
//    //    move(0.f, speed_ * elapsed.asSeconds());
//    //    auto bounding_box = getGlobalBounds();
//    //    bool valid_direction = true;
//    //    for (auto wall : map_.ReturnWalls()) {
//    //        if (bounding_box.intersects(wall.getGlobalBounds())) {
//    //            move(0.f, -speed_ * elapsed.asSeconds());
//    //            valid_direction = false;
//    //            break;
//    //        }
//    //    }
//    //    if (valid_direction) {
//    //        move(0.f, -speed_ * elapsed.asSeconds());
//    //        last_direction_ = new_direction_;
//    //        new_direction_ = 0;
//    //    }
//    //}
//    //if (new_direction_ == 4) {
//    //    new_direction_ = 4;
//    //    move(0.f, -speed_ * elapsed.asSeconds());
//    //    auto bounding_box = getGlobalBounds();
//    //    bool valid_direction = true;
//    //    for (auto wall : map_.ReturnWalls()) {
//    //        if (bounding_box.intersects(wall.getGlobalBounds())) {
//    //            move(0.f, speed_ * elapsed.asSeconds());
//    //            valid_direction = false;
//    //            break;
//    //        }
//    //    }
//    //    if (valid_direction) {
//    //        move(0.f, speed_ * elapsed.asSeconds());
//    //        last_direction_ = new_direction_;
//    //        new_direction_ = 0;
//    //    }
//    //}
//    if (last_direction_ == 1) {
//        move(speed_ * elapsed.asSeconds(), 0.f);
//        //get his bounding box
//        auto bounding_box = getGlobalBounds();
//        //check if it overlaps with a wall
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                //if so, move him back same amount
//                move(-speed_ * elapsed.asSeconds(), 0.f);
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//    if (last_direction_ == 2) {
//        move(-speed_ * elapsed.asSeconds(), 0.f);
//        auto bounding_box = getGlobalBounds();
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(speed_ * elapsed.asSeconds(), 0.f);
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//    if (last_direction_ == 3) {
//        move(0.f, speed_ * elapsed.asSeconds());
//        auto bounding_box = getGlobalBounds();
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(0.f, -speed_ * elapsed.asSeconds());
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//    if (last_direction_ == 4) {
//        move(0.f, -speed_ * elapsed.asSeconds());
//        auto bounding_box = getGlobalBounds();
//        for (auto wall : map_.ReturnWalls()) {
//            if (bounding_box.intersects(wall.getGlobalBounds())) {
//                move(0.f, speed_ * elapsed.asSeconds());
//                last_direction_ = 0;
//                break;
//            }
//        }
//    }
//}
//
//Item::Item(Map& map, int position_x, int position_y) : map_(map), sf::CircleShape(map_.SquareSize() / 12) {
//    setPosition(position_x * map_.SquareSize() + map_.SquareSize() / 2, position_y * map_.SquareSize() + map_.SquareSize() / 2);
//    setFillColor(sf::Color::Yellow);
//}
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 220), "SFML works!");
//    Map map(window);
//    //Player player(map);
//
//    sf::Clock clock;
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//        auto elapsed = clock.restart();
//        window.clear();
//        map.Animate(elapsed);
//        map.Draw();
//        window.display();
//    }
//
//    return 0;
//}
