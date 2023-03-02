#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.h"

#ifndef FOOD_H
#define FOOD_H

class Food: public Entity
{
    public:
        Food() = delete;
        Food(const sf::Vector2f& position);

    private:
        sf::Texture texture;
        sf::Sprite sprite;

    public:
        void update(class World&, const sf::Time&) {};
        void draw(sf::RenderTarget&);

        const sf::Vector2f& get_position() const;
        int get_z_index() override;

        static void spawn_at_random(class World&);
};

#endif
