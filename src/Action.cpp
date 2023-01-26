#include "Action.h"

#include <algorithm>

Action::Action(const Conditions& preconditions, const Conditions& postconditions)
    : _preconditions { preconditions },
      _postconditions { postconditions }
{}

bool Action::is_successor_of(const Action& other) const
{
    return all_satisfied_by(_preconditions, other._postconditions);
}

const Conditions& Action::get_postconditions() const
{
    return _postconditions;
}
