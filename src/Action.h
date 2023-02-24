#include <vector>
#include <string>

#include "Condition.h"

#ifndef ACTION_H
#define ACTION_H

class Action {
    public:
        using Name = std::string;
        using ID = std::size_t;

    public:
        Action(const Conditions& preconditions, const Conditions& postconditions);
        Action(const Name& name, const Conditions& preconditions, const Conditions& postconditions);

        const std::string& get_name() const;

        ID get_id() const;

        bool is_successor_of(const Action&) const;

        const Conditions& get_postconditions() const;

        bool operator==(const Action& other) const;

    private:
        Name _name;
        ID _id;
        Conditions _preconditions;
        Conditions _postconditions;
};

#endif
