#include <vector>

#include "Condition.h"

#ifndef ACTION_H
#define ACTION_H

class Action {
    public:
        Action(const Conditions& preconditions, const Conditions& postconditions);

        bool is_successor_of(const Action&) const;

    private:
        const Conditions _preconditions;
        const Conditions _postconditions;
};

#endif
