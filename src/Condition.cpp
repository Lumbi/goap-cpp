#include "Condition.h"

Condition::Condition(Condition::ID identifier, bool is_true)
    : _identifier { identifier },
      _is_true { is_true }
{}

Condition::Condition(const Condition& other)
{
    this->_identifier = other._identifier;
    this->_is_true = other._is_true;
}

Condition::~Condition() {}

bool Condition::operator== (const Condition& other) const
{
    return this->_identifier == other._identifier;
}

bool Condition::is_satisfied_by(const Condition& other) const
{
    return this->_identifier == other._identifier
        && this->_is_true == other._is_true;
}