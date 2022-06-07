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
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        map.Draw();
        window.display();
    }

    return 0;
}