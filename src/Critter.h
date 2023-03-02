#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "ActionGraph.h"
#include "Action.h"
#include "SpriteAnimator.h"

#ifndef CRITTER_H
#define CRITTER_H

class Critter;
class World;

namespace AI {
    static const Condition hungry(1 << 0, true);
    static const Condition not_hungry = hungry.negated();

    static const Condition food_nearby(1 << 1, true);
    static const Condition no_food_nearby = food_nearby.negated();

    static const Action seek_food(
        "seek_food",
        { food_nearby },
        { not_hungry }
    );

    static const Action sleep(
        "sleep",
        { no_food_nearby },
        { food_nearby }
    );
};

class CritterState
{
    public:
        class State
        {
            public:
                virtual ~State() {};

                virtual void update(Critter&, World&, const sf::Time&) = 0;
                virtual void draw(Critter&, sf::RenderTarget&) = 0;
        };

        class SeekFood: public State
        {
            private:
                float random_move_time;
                float random_move_duration = 1.f;

            public:
                void update(Critter&, World&, const sf::Time&) override;
                void draw(Critter&, sf::RenderTarget&) override;
        };

        class Sleep: public State
        {
            public:
                void update(Critter&, World&, const sf::Time&) override;
                void draw(Critter&, sf::RenderTarget&) override;
        };

    private:
        State* current = nullptr;

    public:
        void update(Critter&, World&, const sf::Time&);
        void draw(Critter&, sf::RenderTarget&);
};

class Critter: public Entity
{
    friend class CritterState;
    friend class CritterState::SeekFood;
    friend class CritterState::Sleep;

    public:
        enum Direction { up, down, left, right };

    public:
        explicit Critter(const sf::Vector2f&);

    private:
        // AI

        CritterState state_machine;
        CritterState::SeekFood seek_food;
        CritterState::Sleep sleep;
        ActionGraph action_graph;

        // Movement

        Direction direction = down;
        float move_speed = 32.f; // units per second

        // Hunger

        int hunger = 50; // 0 == satiated
        static const int max_hunger = 100;
        float hunger_tick_time = 0.f;
        const float hunger_tick_duration = 3.f;

        // Graphics

        sf::Texture spritesheet;
        sf::Sprite sprite;

        sf::Texture sleep_texture;
        sf::Sprite sleep_sprite;

        // Animation

        SpriteAnimator walk_animator;
        SpriteAnimator sleep_animator;

    public:
        void update(World&, const sf::Time&) override;
        void draw(sf::RenderTarget&) override;

        const sf::Vector2f& get_position() const;
        int get_hunger() const;

        void eat(const class Food&);

    private:
        void update_hunger(World&, const sf::Time&);
        void update_eating(World&, const sf::Time&);
        void set_hunger(int);
};

#endif