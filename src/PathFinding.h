#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <limits>

#ifndef PATH_FINDING_H
#define PATH_FINDING_H

template<typename Node, typename Key>
std::vector<Node*> find_shortest_path(
    Node& start,
    std::function<Key (Node&)> get_key,
    std::function<std::vector<Node*> (Node&)> get_neighbors,
    std::function<bool (Node&)> is_goal
)
{
    std::vector<Node*> to_visit;
    std::map<Key, bool> visited;
    std::map<Key, float> distance;
    std::map<Key, Node*> previous;

    to_visit.push_back(&start);
    distance[get_key(start)] = 0;

    Node* last = nullptr;

    // Convenience distance accessor
    auto get_distance = [&](Node& node) -> float {
        Key key = get_key(node);
        return distance.find(key) != distance.end()
            ? distance[key]
            : std::numeric_limits<float>::infinity();
    };

    while (to_visit.empty() == false) {
        // Find the nearest node to visit
        auto it_nearest = std::min_element(
            to_visit.cbegin(),
            to_visit.cend(),
            [&] (auto&& node_a, auto&& node_b) { return get_distance(*node_a) < get_distance(*node_a); }
        );

        // Pop it
        Node* nearest = *it_nearest;
        to_visit.erase(it_nearest);

        // Exit if we're at goal
        if (is_goal(*nearest)) {
            last = nearest;
            break;
        }

        // Skip if already visited
        if (visited[get_key(*nearest)]) {
            continue;
        } else {
            visited[get_key(*nearest)] = true;
        }

        // Explore neighbors and calculate distances
        for (auto&& neighbor : get_neighbors(*nearest)) {
            if (visited[get_key(*neighbor)] == false) {
                to_visit.push_back(neighbor);
                float new_distance = get_distance(*nearest) + 1.f; // default distance to 1 between nodes
                float known_distance = get_distance(*neighbor);
                if (new_distance < known_distance) {
                    distance[get_key(*neighbor)] = new_distance;
                    previous[get_key(*neighbor)] = nearest;
                }
            }
        }
    }

    // Reconstruct path
    std::vector<Node*> path;
    Node* current = last;
    while (current) {
        path.push_back(current);
        Key key = get_key(*current);
        if (previous.find(key) != previous.end()) {
            current = previous[key];
        } else {
            current = nullptr;
        }
    }

    return path;
}

#endif