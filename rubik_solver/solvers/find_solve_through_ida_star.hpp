#pragma once

#include "HeuristicDB.hpp"

struct StateNode {
    StateNode(const Cube& cube, uint8_t depth, Cube::Rotation rotation)
            : cube(cube), depth(depth), rotation(rotation) {}

    Cube cube;
    uint8_t depth;
    Cube::Rotation rotation;
};

struct PriorityNode {
    PriorityNode(const Cube& cube, Cube::Rotation rotation, uint8_t priority)
            : cube(cube), rotation(rotation), priority(priority) {}

    Cube cube;
    Cube::Rotation rotation;
    uint8_t priority; // Priority

    bool operator>(const PriorityNode& node) const {
        if (priority == node.priority) {
            return rotation < node.rotation;
        }
        return priority > node.priority;
    }
};

template<size_t MaxRotationsSize, class Heuristic, size_t RotationsSize>
std::vector<Cube::Rotation> find_solve_through_ida_star(
        Heuristic heuristic, const Cube& cube, std::array<Cube::Rotation, RotationsSize> possible_rotations,
        bool (*IsSolve)(const Cube& cube)) {
    std::stack<StateNode> nodes;
    std::array<Cube::Rotation, MaxRotationsSize> rotations;

    /// -1 because it's become normal on the first run. (++current_optimal_estimate)
    uint8_t current_optimal_estimate = heuristic.GetEstimatedMovesNumber(cube) - 1;
    uint8_t max_depth = 0;

    while (true) {
        if (nodes.empty()) {
            nodes.emplace(cube, 0, Cube::Rotation::None);
            ++current_optimal_estimate;
        }

        StateNode current_node = nodes.top();
        nodes.pop();

        if (max_depth < current_node.depth) {
            max_depth = current_node.depth;
        }
        rotations[current_node.depth] = current_node.rotation;

        if (current_node.depth == current_optimal_estimate) {
            if (IsSolve(current_node.cube)) { break; }
            continue;
        }

        for (auto rotation: possible_rotations) {
            Cube new_cube_state = Cube::Rotate(current_node.cube, rotation);
            uint8_t dh = current_node.depth + 1 + heuristic.GetEstimatedMovesNumber(new_cube_state);
            if (dh <= current_optimal_estimate) {
                nodes.emplace(new_cube_state, current_node.depth + 1, rotation);
            }
        }
    }

    std::vector<Cube::Rotation> res_rotations;
    for (uint8_t i = 0; i <= max_depth; ++i) {
        if (rotations[i] != Cube::Rotation::None) {
            res_rotations.push_back(rotations[i]);
        }
    }

    return res_rotations;
}
