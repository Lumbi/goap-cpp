#include <iostream>
#include <vector>

#include "Action.h"
#include "Goal.h"

#ifndef ACTION_GRAPH_H
#define ACTION_GRAPH_H

class ActionGraph
{
    public:
        class Node
        {
            public:
                explicit Node(const Action& action);

                const std::vector<Node*>& get_successors() const;
                void add_successor(Node* node);

            public:
                const Action action;

            private:
                std::vector<Node*> _successors;
        };

    public:
        ActionGraph(const ActionGraph&) = delete;
        ActionGraph& operator=(const ActionGraph&) = delete;

        ActionGraph(const std::vector<const Action>& actions);

        ~ActionGraph();

        const std::vector<Node*>& get_nodes() const;

        std::vector<Action> find_path(const Conditions& start_conditions, const Goal& goal) const;

    private:
        std::vector<Node*> _nodes;

    // Path Finding

    public:
        struct PathFindingQuery
        {
            using Node = ActionGraph::Node;
            using Key = Action::ID;

            Node* start;
            Goal goal;

            Node* get_start();
            Key get_key(const Node&);
            const std::vector<Node*>& get_neighbors(const Node&);
            bool is_goal(const Node&);
        };
};

std::ostream& operator<< (std::ostream& os, const ActionGraph::Node& node);
std::ostream& operator<< (std::ostream& os, const ActionGraph& graph);

#endif
