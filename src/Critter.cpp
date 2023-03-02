#include "Critter.h"

#include <SFML/Graphics.hpp>

#include "World.h"
#include "Food.h"

Critter::Critter(const sf::Vector2f& position)
    : action_graph({ AI::seek_food, AI::sleep })
{
    switch (rand() % 4) {
        case 1:
            spritesheet.loadFromFile("res/Slime_Medium_Blue.png");
            break;
        case 2:
            spritesheet.loadFromFile("res/Slime_Medium_Green.png");
            break;
        case 3:
            spritesheet.loadFromFile("res/Slime_Medium_Red.png");
            break;
        default:
            spritesheet.loadFromFile("res/Slime_Medium_White.png");
            break;
    }

    int frame_size = 32;
    sprite.setTexture(spritesheet);
    sprite.setOrigin(frame_size / 2, frame_size / 2);
    sprite.setScale(2, 2);
    sprite.setPosition(position);

    walk_animator.set_mode(SpriteAnimator::PlayMode::loop);
    walk_animator.set_fps(15.f);
    walk_animator.set_frame_count(spritesheet.getSize().x / frame_size);
    walk_animator.set_frame_size({ frame_size, frame_size });

    int sleep_frame_size = 16;
    sleep_texture.loadFromFile("res/sleep.png");
    sleep_sprite.setTexture(sleep_texture);
    sleep_sprite.setOrigin(0, sleep_frame_size); // bottom-left

    sleep_animator.set_mode(SpriteAnimator::PlayMode::loop);
    sleep_animator.set_fps(8.f);
    sleep_animator.set_frame_count(sleep_texture.getSize().x / sleep_frame_size);
    sleep_animator.set_frame_size({ sleep_frame_size, sleep_frame_size });
}

void Critter::update(World& world, const sf::Time& delta_time)
{
    update_hunger(world, delta_time);
    update_eating(world, delta_time);
    state_machine.update(*this, world, delta_time);
}

const sf::Vector2f& Critter::get_position() const
{
    return sprite.getPosition();
}

void Critter::eat(const class Food& food)
{
    set_hunger(hunger - 10);
}

void Critter::update_hunger(World& world, const sf::Time& delta_time)
{
    hunger_tick_time += delta_time.asSeconds();
    if (hunger_tick_time >= hunger_tick_duration) {
        hunger_tick_time = 0;
        set_hunger(hunger + 1);
    }

    if (hunger >= Critter::max_hunger) {
        world.destroy(this);
    }
}

int Critter::get_hunger() const
{
    return hunger;
}

void Critter::set_hunger(int new_hunger)
{
    hunger = new_hunger;
    if (hunger < 0) {
        hunger = 0;
    }
}

void Critter::update_eating(World& world, const sf::Time& delta_time)
{
    for (auto&& other : world.entities) {
        auto food = dynamic_cast<Food*>(other.get());
        if (!food) { continue; }
        if (World::distance(get_position(), food->get_position()) < 20) {
            eat(*food);
            world.destroy(other.get());
        }
    }
}

void Critter::draw(sf::RenderTarget& render)
{
    render.draw(sprite);
    state_machine.draw(*this, render);
}

// AI & State

Conditions get_world_conditions(World& world, Critter& critter)
{
    Conditions conditions;

    if (critter.get_hunger() > 50) {
        conditions.push_back(AI::hungry);
    } else {
        conditions.push_back(AI::not_hungry);
    }

    if (world.food_count_nearby(critter.get_position()) > 0) {
        conditions.push_back(AI::food_nearby);
    } else {
        conditions.push_back(AI::no_food_nearby);
    }

    return conditions;
}

void CritterState::update(Critter& critter, World& world, const sf::Time& delta_time)
{
    if (!current) {
        current = &critter.seek_food;
    }

    current->update(critter, world, delta_time);

    Conditions world_condition = get_world_conditions(world, critter);
    auto path = critter.action_graph.find_path(world_condition, Goal({ AI::not_hungry }));

    if (!path.empty()) {
        Action& next_action = path.front();
        if (next_action == AI::seek_food) {
            current = &critter.seek_food;
        } else if (next_action == AI::sleep) {
            current = &critter.sleep;
        }
    }
}

void CritterState::draw(Critter& critter, sf::RenderTarget& render)
{
    if (current) {
        current->draw(critter, render);
    }
}

void CritterState::SeekFood::update(Critter& critter, World& world, const sf::Time& delta_time)
{
    random_move_time += delta_time.asSeconds();

    if (random_move_time >= random_move_duration) {
        random_move_time = 0;
        random_move_duration = float(1 + (rand() % 4));

        critter.direction = static_cast<Critter::Direction>(rand() % 4);
    }

    float delta = critter.move_speed * delta_time.asSeconds();
    switch (critter.direction) {
        case Critter::Direction::up: critter.sprite.move(0, -delta); break;
        case Critter::Direction::down: critter.sprite.move(0, delta); break;
        case Critter::Direction::left: critter.sprite.move(-delta, 0); break;
        case Critter::Direction::right: critter.sprite.move(delta, 0); break;
    }

    critter.walk_animator.update(critter.sprite, delta_time);
}

void CritterState::SeekFood::draw(Critter&, sf::RenderTarget&)
{
    // NOOP
}

void CritterState::Sleep::update(Critter& critter, World& world, const sf::Time& delta_time)
{
    critter.sleep_animator.update(critter.sleep_sprite, delta_time);
    critter.sleep_sprite.setPosition(critter.sprite.getPosition() + sf::Vector2f(16, 0));
}

void CritterState::Sleep::draw(Critter& critter, sf::RenderTarget& render)
{
    render.draw(critter.sleep_sprite);
}
