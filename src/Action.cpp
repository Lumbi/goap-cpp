#include "Action.h"

#include <algorithm>
#include "Condition.h"

Action::Action(const ConditionSet& preconditions, const ConditionSet& postconditions)
    : _preconditions { preconditions },
      _postconditions { postconditions }
{}

Action::~Action() {}

bool Action::is_successor_of(const Action& other)
{
    for (auto &&precondition : _preconditions)
    {
        auto found = std::find(other._postconditions.cbegin(), other._postconditions.cend(), precondition);
        if (found == other._postconditions.cend()) { return false; }
        if (precondition.is_satisfied_by(*found) == false) { return false; }
    }
    return true;
}