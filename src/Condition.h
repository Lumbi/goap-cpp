#include <vector>

#ifndef CONDITION_H
#define CONDITION_H

class Condition
{
    public:
        using ID = int;

    public:
        Condition() = delete;
        Condition(ID identifier, bool is_true);
        Condition(const Condition&);
        Condition(Condition&&) = delete;

        ~Condition();

        bool is_satisfied_by(const Condition&) const;

        bool operator== (const Condition& other) const;

    private:
        ID _identifier;
        bool _is_true;
};

using Conditions = std::vector<const Condition>;

#endif