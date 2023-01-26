#include "Condition.h"

#ifndef GOAL_H
#define GOAL_H

class Action;

class Goal
{
    public:
        Goal(const Conditions&);

        bool is_reachable_by(const Action&) const;

    private:
        Conditions _preconditions;
};

#endif
