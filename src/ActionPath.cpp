#include "ActionPath.h"

ActionPath::ActionPath(const Action& action)
    : _actions({ action })
{}

const std::vector<const Action>& ActionPath::get_actions() const
{
    return _actions;
}

void ActionPath::add_next(const Action& action)
{
    _actions.push_back(action);
}
