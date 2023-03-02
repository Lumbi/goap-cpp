#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#ifndef WORLD_H
#define WORLD_H

class World {
    public:
        World() = default;
        World(const World&) = delete;
        World& operator=(const World&) = delete ;

    public:
        sf::IntRect bounds = { 0, 0, 1024, 768 };
        std::vector<std::unique_ptr<class Entity>> entities;

    private:
        float food_spawn_time = 0.f;
        float food_spawn_delay = 1.f;
        int destroyed_count = 0;

    public:
        void update(const sf::Time&);
        void draw(sf::RenderTarget&);

        void destroy(Entity*);

        static float distance(const sf::Vector2f&, const sf::Vector2f&);
        int food_count_nearby(const sf::Vector2f& position);
};

#endif