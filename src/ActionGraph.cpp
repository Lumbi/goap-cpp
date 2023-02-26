#include "ActionGraph.h"

#include "Goal.h"
#include "PathFinding.h"

#include <algorithm>

ActionGraph::Node::Node(const Action& action)
    : action { action },
      _successors { }
{}

const std::vector<ActionGraph::Node*>& ActionGraph::Node::get_successors() const
{
    return _successors;
}

void ActionGraph::Node::add_successor(Node* node)
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
    std::vector<Node*> shortest_path;

    // Consider each node as a possible starting point
    for (auto&& start : _nodes) {
        if (start->action.is_reachable_from(start_conditions)) {
            PathFindingQuery query { start, goal };
            std::vector<Node*> path = find_shortest_path<PathFindingQuery>(query);
            if (shortest_path.empty() || path.size() < shortest_path.size()) {
                shortest_path = std::move(path);
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

// Path Finding

ActionGraph::PathFindingQuery::Node* ActionGraph::PathFindingQuery::get_start()
{
    return start;
}

ActionGraph::PathFindingQuery::Key ActionGraph::PathFindingQuery::get_key(const ActionGraph::PathFindingQuery::Node& node)
{
    return node.action.get_id();
}

const std::vector<ActionGraph::PathFindingQuery::Node*>& ActionGraph::PathFindingQuery::get_neighbors(const ActionGraph::PathFindingQuery::Node& node)
{
    return node.get_successors();
}

bool ActionGraph::PathFindingQuery::PathFindingQuery::is_goal(const ActionGraph::PathFindingQuery::Node& node)
{
    return goal.is_reachable_by(node.action);
}

// Debug

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