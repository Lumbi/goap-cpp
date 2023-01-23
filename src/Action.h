#include <vector>

#ifndef ACTION_H
#define ACTION_H

class Condition;

class Action {
    public:
        using ConditionSet = std::vector<const Condition>;

    public:
        Action() = delete;
        Action(const Action&) = delete;
        Action(const Action&&) = delete;
        Action(const ConditionSet& preconditions, const ConditionSet& postconditions);

        ~Action();

        bool is_successor_of(const Action&);

    private:
        const ConditionSet _preconditions;
        const ConditionSet _postconditions;
};

#endif
