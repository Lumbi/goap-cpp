#include "Food.h"

#include <memory>

#include "World.h"

static int sprite_size = 16;

Food::Food(const sf::Vector2f& position)
{
    texture.loadFromFile("res/fruits.png");
    sprite.setTexture(texture);
    int u = (rand() % 3) * sprite_size;
    int v = (rand() % 3) * sprite_size;
    sprite.setTextureRect(sf::IntRect(u, v, sprite_size, sprite_size));
    sprite.setPosition(position);
    sprite.setOrigin(sprite_size / 2, sprite_size / 2);
}

void Food::draw(sf::RenderTarget& render)
{
    render.draw(sprite);
}

const sf::Vector2f& Food::get_position() const
{
    return sprite.getPosition();
}

void Food::spawn_at_random(World& world)
{
    auto food = std::make_unique<Food>(
        sf::Vector2f({
            float(world.bounds.left + (rand() % world.bounds.width)),
            float(world.bounds.top + (rand() % world.bounds.height)),
        })
    );
    world.entities.push_back(std::move(food));
}