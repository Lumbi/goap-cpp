#include "Condition.h"

Condition::Condition(Condition::ID identifier, bool is_true)
    : _identifier { identifier },
      _is_true { is_true }
{}

bool Condition::operator== (const Condition& other) const
{
    return this->_identifier == other._identifier;
}

Condition Condition::negated() const
{
    return Condition(_identifier, !_is_true);
}

bool Condition::is_satisfied_by(const Condition& other) const
{
    return this->_identifier == other._identifier
        && this->_is_true == other._is_true;
}

bool all_satisfied_by(const Conditions& preconditions, const Conditions& postconditions)
{
    for (auto &&precondition : preconditions)
    {
        auto found = std::find(postconditions.cbegin(), postconditions.cend(), precondition);
        if (found == postconditions.cend()) { return false; }
        if (precondition.is_satisfied_by(*found) == false) { return false; }
    }
    return true;
}
