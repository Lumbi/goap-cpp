#include <SFML/Graphics.hpp>

#ifndef CRITTER_H
#define CRITTER_H

class Critter
{
    public:
        explicit Critter();

        void update(const sf::Time& delta_time);
        void draw(sf::RenderTarget&);

    public:
        sf::Vector2f position;
        float rotation;

    private:
        sf::Texture spritesheet;
        sf::Sprite sprite;

        float animation_frame_time = 0.f;
        const float animation_frame_duration = 7.f / 60.f;
        int animation_frame_index = 0;
        int animation_frame_count;
        int animation_frame_size = 32;
};

#endif