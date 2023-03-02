#include "SpriteAnimator.h"

void SpriteAnimator::set_mode(SpriteAnimator::PlayMode mode)
{
    play_mode = mode;
}

void SpriteAnimator::set_frame_size(sf::Vector2i size)
{
    frame_size = size;
}

void SpriteAnimator::set_frame_count(int count)
{
    frame_count = count;
}

void SpriteAnimator::set_fps(float fps)
{
    frames_per_second = fps;
}

void SpriteAnimator::update(sf::Sprite& sprite, const sf::Time& delta_time)
{
    if (!is_playing) { return; }

    time += delta_time.asSeconds();

    float duration = frame_count / frames_per_second;
    if (time >= duration) {
        switch (play_mode) {
            case PlayMode::once:
                is_playing = false;
                time = duration;
                break;
            case PlayMode::loop:
                time = 0;
                break;
        }
    }

    int next_frame_index = (time / duration) * frame_count;
    if (next_frame_index != frame_index) {
        frame_index = next_frame_index;
        sprite.setTextureRect(
            sf::IntRect(
                frame_start.x + (frame_index * frame_size.x),
                frame_start.y,
                frame_size.x,
                frame_size.y
            )
        );
    }
}
