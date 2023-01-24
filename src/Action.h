#include <vector>

#include "Condition.h"

#ifndef ACTION_H
#define ACTION_H

class Action {
    public:
        using ConditionSet = std::vector<const Condition>;

    public:
        Action(const ConditionSet& preconditions, const ConditionSet& postconditions);

        bool is_successor_of(const Action&) const;

    private:
        const ConditionSet _preconditions;
        const ConditionSet _postconditions;
};

#endif
