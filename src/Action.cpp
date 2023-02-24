#include "Action.h"

#include <algorithm>
#include <string>

static int ACTION_NAME_SEQUENCE = 0;

Action::Action(const Conditions& preconditions, const Conditions& postconditions)
    : Action("__action_seq_" + std::to_string(ACTION_NAME_SEQUENCE), preconditions, postconditions)
{
    ACTION_NAME_SEQUENCE += 1;
}

Action::Action(const Name& name, const Conditions& preconditions, const Conditions& postconditions)
    : _name { name },
      _id { std::hash<std::string>{}(name) },
      _preconditions { preconditions },
      _postconditions { postconditions }
{}

const Action::Name& Action::get_name() const
{
    return _name;
}

Action::ID Action::get_id() const
{
    return _id;
}

bool Action::is_successor_of(const Action& other) const
{
    return is_reachable_from(other._postconditions);
}

bool Action::is_reachable_from(const Conditions& conditions) const
{
    return all_satisfied_by(_preconditions, conditions);
}

const Conditions& Action::get_postconditions() const
{
    return _postconditions;
}

bool Action::operator==(const Action& other) const
{
    return this->_name == other._name;
}
