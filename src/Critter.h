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
    static const Condition hungry(1, true);
    static const Condition not_hungry = hungry.negated();

    static const Condition food_nearby(2, true);
    static const Condition no_food_nearby = food_nearby.negated();

    static const Condition satiated(3, true);

    static const Condition powered_up(4, true);

    static const Action seek_food(
        "seek_food",
        { food_nearby },
        { not_hungry, satiated }
    );

    static const Action sleep(
        "sleep",
        { no_food_nearby },
        { food_nearby }
    );

    static const Action power_up(
        "power_up",
        { not_hungry, satiated },
        { powered_up }
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

        class PowerUp: public State
        {
            private:
                const float initial_scale = 2.f;
                const float target_scale = 4.f;
                float animation_time = 0.f;
                float animation_duration = 3.f;

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
    friend class CritterState::PowerUp;

    public:
        enum Direction { up, down, left, right };

    public:
        explicit Critter(const sf::Vector2f&);

    private:
        // AI

        CritterState state_machine;
        CritterState::SeekFood seek_food;
        CritterState::Sleep sleep;
        CritterState::PowerUp power_up;
        ActionGraph action_graph;

        // Movement

        Direction direction = down;
        float move_speed = 32.f; // units per second

        // Hunger

        int hunger = 50; // 0 == satiated
        static const int max_hunger = 100;
        float hunger_tick_time = 0.f;
        const float hunger_tick_duration = 3.f;

        // Power

        bool is_powered_up = false;

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
        int get_z_index() override;

        int get_hunger() const;

        void eat(const class Food&);

    private:
        void update_hunger(World&, const sf::Time&);
        void update_eating(World&, const sf::Time&);
        void set_hunger(int);
};

#endif