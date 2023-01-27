#include <vector>
#include <string>

#include "Condition.h"

#ifndef ACTION_H
#define ACTION_H

class Action {
    public:
        using Name = std::string;

    public:
        Action(const Conditions& preconditions, const Conditions& postconditions);
        Action(const Name& name, const Conditions& preconditions, const Conditions& postconditions);

        const std::string& get_name() const;
        bool is_successor_of(const Action&) const;

        const Conditions& get_postconditions() const;

    private:
        const Name _name;
        const Conditions _preconditions;
        const Conditions _postconditions;
};

#endif
