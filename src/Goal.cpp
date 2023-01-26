#include "Goal.h"
#include "Action.h"

Goal::Goal(const Conditions& preconditions)
    : _preconditions(preconditions)
{}

bool Goal::is_reachable_by(const Action& action) const
{
    return all_satisfied_by(_preconditions, action.get_postconditions());
}
