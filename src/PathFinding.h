#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <limits>

#ifndef PATH_FINDING_H
#define PATH_FINDING_H

template<typename Query>
concept PathFindingQueryable =
requires
{
    typename Query::Node;
    typename Query::Key;
}
&&
requires (Query query, typename Query::Node node)
{
    { query.get_start() } -> std::same_as<typename Query::Node*>;
    { query.get_key(node) } -> std::convertible_to<typename Query::Key>;
    { query.get_neighbors(node) } -> std::convertible_to<std::vector<typename Query::Node*>>;
    { query.is_goal(node) } -> std::same_as<bool>;
};

template<typename Query>
requires PathFindingQueryable<Query>
std::vector<typename Query::Node*> find_shortest_path(Query& query)
{
    using Key = typename Query::Key;
    using Node = typename Query::Node;

    Node* start = query.get_start();
    if (!start) { return {}; }

    std::vector<Node*> to_visit;
    std::unordered_set<Key> visited;
    std::unordered_map<Key, float> distance;
    std::unordered_map<Key, Node*> previous;

    to_visit.push_back(start);
    distance[query.get_key(*start)] = 0;

    Node* last = nullptr;

    // Convenience distance accessor
    auto get_distance = [&](Node& node) -> float {
        Key key = query.get_key(node);
        return distance.contains(key)
            ? distance[key]
            : std::numeric_limits<float>::infinity();
    };

    while (!to_visit.empty()) {
        // Find the nearest node to visit
        auto it_nearest = std::min_element(
            to_visit.cbegin(),
            to_visit.cend(),
            [&] (auto&& node_a, auto&& node_b) { return get_distance(*node_a) < get_distance(*node_b); }
        );

        // Pop it
        Node* nearest = *it_nearest;
        to_visit.erase(it_nearest);

        // Exit if we're at goal
        if (query.is_goal(*nearest)) {
            last = nearest;
            break;
        }

        // Skip if already visited
        Key nearest_key = query.get_key(*nearest);
        if (visited.contains(nearest_key)) {
            continue;
        } else {
            visited.insert(nearest_key);
        }

        // Explore neighbors and calculate distances
        for (auto&& neighbor : query.get_neighbors(*nearest)) {
            Key neighbor_key = query.get_key(*neighbor);
            if (!visited.contains(neighbor_key)) {
                to_visit.push_back(neighbor);
                float new_distance = get_distance(*nearest) + 1.f; // default distance to 1 between nodes
                float known_distance = get_distance(*neighbor);
                if (new_distance < known_distance) {
                    distance[neighbor_key] = new_distance;
                    previous[neighbor_key] = nearest;
                }
            }
        }
    }

    // Reconstruct path
    std::vector<Node*> path;
    Node* current = last;
    while (current) {
        path.push_back(current);
        Key key = query.get_key(*current);
        if (previous.contains(key)) {
            current = previous[key];
        } else {
            current = nullptr;
        }
    }

    return path;
}

#endif