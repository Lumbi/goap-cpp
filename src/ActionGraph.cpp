#include "ActionGraph.h"

#include "Goal.h"
#include "PathFinding.h"

#include <algorithm>

ActionGraph::Node::Node(const Action& action)
    : action { action },
      _successors { }
{}

const std::vector<const ActionGraph::Node*>& ActionGraph::Node::get_successors() const
{
    return _successors;
}

void ActionGraph::Node::add_successor(const Node* node)
{
    if (node != nullptr) {
        _successors.push_back(node);
    }
}

ActionGraph::ActionGraph(const std::vector<const Action>& actions)
{
    for (auto &&action : actions)
    {
        _nodes.push_back(new Node { action });
    }

    for (auto &&node : _nodes)
    {
        for (auto other = _nodes.cbegin(); other != _nodes.cend(); other++)
        {
            if (node == *other) { continue; } // Skip if itself

            if ((*other)->action.is_successor_of(node->action)) {
                node->add_successor(*other);
            }
        }
    }
}

ActionGraph::~ActionGraph()
{
    for (auto &&node : _nodes)
    {
        delete node;
    }
}

const std::vector<ActionGraph::Node*>& ActionGraph::get_nodes() const
{
    return _nodes;
}

std::vector<Action> ActionGraph::find_path(const Conditions& start_conditions, const Goal& goal) const
{
    std::vector<const Node*> shortest_path;

    // Consider each node as a possible starting point
    for (auto&& node : _nodes) {
        if (node->action.is_reachable_from(start_conditions)) {
            std::vector<const Node*> path = find_shortest_path<const Node, Action::ID>(
                *node,
                [] (const Node& node) { return node.action.get_id(); },
                [] (const Node& node) { return node.get_successors(); },
                [&] (const Node& node) { return goal.is_reachable_by(node.action); }
            );
            if (shortest_path.empty()) {
                shortest_path = path;
            } else if (path.size() < shortest_path.size()) {
                shortest_path = path;
            }
        }
    }

    // Map nodes to actions
    std::vector<Action> actions;
    std::transform(
        shortest_path.rbegin(), shortest_path.rend(),
        std::back_inserter(actions),
        [](auto&& node){ return node->action; }
    );
    return actions;
}

std::ostream& operator<< (std::ostream& os, const ActionGraph::Node& node)
{
    return os << "Node(" << &node.action << ")";
}

std::ostream& operator<< (std::ostream& os, const ActionGraph& graph)
{
    os << "Graph(" << std::endl;
    for (auto &&node : graph.get_nodes())
    {
        os << '\t';
        os << *node << "->";
        for (auto &&successor : node->get_successors())
        {
            os << *successor << ", ";
        }
        os << std::endl;
    }
    os << ")";
    return os;
}