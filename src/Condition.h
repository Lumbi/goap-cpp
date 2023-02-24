#include <vector>

#ifndef CONDITION_H
#define CONDITION_H

class Condition
{
    public:
        using ID = int;

    public:
        Condition(ID identifier, bool is_true);

        bool is_satisfied_by(const Condition&) const;

        bool operator== (const Condition& other) const;

    private:
        ID _identifier;
        bool _is_true;
};

using Conditions = std::vector<const Condition>;

bool all_satisfied_by(const Conditions& preconditions, const Conditions& postconditions);

#endif