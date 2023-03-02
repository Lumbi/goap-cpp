#include "World.h"

#include <algorithm>
#include <vector>
#include <cmath>

#include "Critter.h"
#include "Food.h"

void World::update(const sf::Time& delta_time)
{
    std::sort(
        entities.begin(),
        entities.end(),
        [](auto&& a, auto&& b){
            if (a != nullptr && b != nullptr) {
                return a->get_z_index() < b->get_z_index();
            } else {
                return true;
            }
        }
    );

    for (auto&& entity : entities) {
        if (entity) {
            entity->update(*this, delta_time);
        }
    }

    // Spawn food
    food_spawn_time += delta_time.asSeconds();
    if (food_spawn_time >= food_spawn_delay) {
        food_spawn_time = 0;
        Food::spawn_at_random(*this);
    }

    // Clean up
    if (destroyed_count > 0) {
        std::erase_if(entities, [](auto&& entity){ return entity.get() == nullptr; });
        destroyed_count = 0;
    }
}

void World::draw(sf::RenderTarget& render)
{
    for (auto&& entity : entities) {
        if (entity) {
            entity->draw(render);
        }
    }
}

void World::destroy(Entity* entity_to_destroy)
{
    // TODO: Dangerous and inefficient, would be nice to use a DOD approach instead
    for (auto&& entity : entities) {
        if (entity.get() == entity_to_destroy) {
            delete entity.release();
            destroyed_count++;
            break;
        }
    }
}

float World::distance(const sf::Vector2f& a,  const sf::Vector2f& b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int World::food_count_nearby(const sf::Vector2f& position)
{
    const float radius = 164.f;
    int count = 0;
    for (auto&& entity : entities) {
        Food* food = dynamic_cast<Food*>(entity.get());
        if (!food) { continue; }
        if (World::distance(position, food->get_position()) <= radius) {
            count++;
        }
    }
    return count;
}
