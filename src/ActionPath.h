#include <vector>

#include "Action.h"

#ifndef ACTION_PATH_H
#define ACTION_PATH_H

class ActionPath
{
    public:
        ActionPath(const Action&);

        const std::vector<const Action>& get_actions() const;

        void add_next(const Action&);

    private:
        std::vector<const Action> _actions;
};

#endif
