#include <iostream>
#include <vector>

#include "Action.h"

#ifndef ACTION_GRAPH_H
#define ACTION_GRAPH_H

class ActionGraph
{
    public:
        class Node
        {
            public:
                explicit Node(const Action& action);

                const std::vector<const Node*> get_successors() const;
                void add_successor(const Node* node);

            public:
                const Action action;

            private:
                std::vector<const Node*> _successors;
        };

    public:
        ActionGraph(const ActionGraph&) = delete;
        ActionGraph(const std::vector<const Action>& actions);

        ~ActionGraph();

        const std::vector<Node*>& get_nodes() const;

        std::vector<Action> find_path(const Conditions& start_conditions, const class Goal& goal) const;

    private:
        std::vector<Node*> _nodes;

};

std::ostream& operator<< (std::ostream& os, const ActionGraph::Node& node);
std::ostream& operator<< (std::ostream& os, const ActionGraph& graph);

#endif
