#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Critter.h"
#include "Food.h"
#include "World.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "GOAP");
    sf::View view = window.getDefaultView();

    World world;

    for (int i = -5; i < 5; i++) {
        auto critter = std::make_unique<Critter>(
            sf::Vector2f({
                float(500 + (i * 10) * (rand() % 5)),
                float(300 + (i * 10) * (rand() % 5))
            })
        );
        world.entities.push_back(std::move(critter));
    }

    sf::Event event;
    sf::Clock clock;
    float target_frame_rate = 60.f;
    float target_time_per_frame = 1.f / target_frame_rate;

    for (int i = 0; i < 100; i++) {
        Food::spawn_at_random(world);
    }

    while (window.isOpen())
    {
        sf::Time delta_time = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visible_area(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visible_area));
            }
        }

        world.update(delta_time);

        window.clear();

        world.draw(window);

        window.display();

        float frame_elapsed_time = clock.getElapsedTime().asSeconds();
        if (frame_elapsed_time < target_time_per_frame) {
            float delay = target_time_per_frame - frame_elapsed_time;
            sf::sleep(sf::seconds(delay));
        }
    }

    return 0;
}
