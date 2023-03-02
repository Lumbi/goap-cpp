#include <SFML/Graphics.hpp>

#ifndef SPRITE_ANIMATOR_H
#define SPRITE_ANIMATOR_H

class SpriteAnimator
{
    public:
        enum PlayMode { once, loop };

    public:
        SpriteAnimator() = default;

    private:
        PlayMode play_mode = PlayMode::once;
        sf::Vector2i frame_start = { 0, 0 };
        sf::Vector2i frame_size = { 32, 32 };
        int frame_count = 1;
        float frames_per_second = 1.f;

        bool is_playing = true;
        int frame_index = -1;
        float time = 0.f;

    public:
        void set_mode(SpriteAnimator::PlayMode);
        void set_frame_size(sf::Vector2i);
        void set_frame_count(int);
        void set_fps(float);

        void update(sf::Sprite&, const sf::Time&);
};

#endif