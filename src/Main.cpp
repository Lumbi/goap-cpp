#include <iostream>
#include <SFML/Graphics.hpp>

#include "Critter.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "GOAP");
    sf::View view = window.getDefaultView();

    Critter critter;
    critter.position = { 100, 100 };

    sf::Event event;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        // UPDATE
        critter.update(deltaTime);

        // DRAW

        window.clear();
        critter.draw(window);
        window.display();
    }

    return 0;
}
