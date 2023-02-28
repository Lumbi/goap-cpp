#include <SFML/Graphics.hpp>

#include "Critter.h"

Critter::Critter()
    : position { 0, 0 },
      rotation { 0 }
{
    spritesheet.loadFromFile("res/Slime_Medium_Blue.png");
    sprite.setTexture(spritesheet);
    sprite.setTextureRect(sf::IntRect(0, 0, animation_frame_size, animation_frame_size));

    sprite.setPosition(position);
    sprite.setRotation(rotation);
    sprite.setScale(2, 2);

    animation_frame_count = spritesheet.getSize().x / animation_frame_size;
}

void Critter::update(const sf::Time& delta_time)
{
    animation_frame_time += delta_time.asSeconds();

    if (animation_frame_time >= animation_frame_duration) {
        animation_frame_time = 0;
        animation_frame_index = (animation_frame_index + 1) % animation_frame_count;

        sprite.setTextureRect(
            sf::IntRect(
                animation_frame_index * animation_frame_size, 0,
                animation_frame_size, animation_frame_size
            )
        );
    }
}


void Critter::draw(sf::RenderTarget& render)
{
    render.draw(sprite);
}
