#include "Condition.h"

#ifndef GOAL_H
#define GOAL_H

class Goal
{
    public:
        explicit Goal(const Conditions&);

        bool is_reachable_by(const class Action&) const;

    private:
        Conditions _preconditions;
};

#endif
