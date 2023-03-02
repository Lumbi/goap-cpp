#include <SFML/Graphics.hpp>

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        virtual ~Entity() { };

        virtual void update(class World&, const sf::Time&) = 0;
        virtual void draw(sf::RenderTarget&) = 0;

        virtual int get_z_index() = 0;
};

#endif
