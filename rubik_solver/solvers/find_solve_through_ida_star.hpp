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
        Heuristic heuristic, const Cube& cube, std::array<Cube::Rotation, RotationsSize> possible_rotations) {
    std::stack<StateNode> nodes;
    std::queue<PriorityNode> tmp_nodes;
    std::array<Cube::Rotation, MaxRotationsSize> rotations;

    uint8_t current_optimal_estimate = heuristic.GetEstimatedMovesNumber(cube) - 1;
    uint8_t max_depth = 0;

    bool is_solved = false;
    while (true) {
        if (nodes.empty()) {
            nodes.emplace(cube, 0, Cube::Rotation::None);
            ++current_optimal_estimate;
        }

        StateNode current_node = nodes.top();
        nodes.pop();
        std::cout << (int) current_optimal_estimate << std::endl;

        if (max_depth < current_node.depth) {
            max_depth = current_node.depth;
        }
        rotations[current_node.depth] = current_node.rotation;

        if (current_node.depth == current_optimal_estimate) {
            if (current_node.cube.IsSolved()) { break; }
            continue;
        }

        for (auto rotation: possible_rotations) {
            Cube new_cube_state = Cube::Rotate(current_node.cube, rotation);
            uint8_t dh = current_node.depth + 1 + heuristic.GetEstimatedMovesNumber(new_cube_state);
            if (dh <= current_optimal_estimate) {
                tmp_nodes.emplace(new_cube_state, rotation, dh);
            }
        }

        while (!tmp_nodes.empty()) {
            nodes.emplace(tmp_nodes.front().cube, current_node.depth + 1, tmp_nodes.front().rotation);
            tmp_nodes.pop();
        }


                /////////////////////////////////
                std::cout << "AAAA" << std::endl;
                if (current_node.rotation == Cube::Rotation::None) {
                    std::cout << "rotation: None" << std::endl;
                }
                else {
                    std::vector<Cube::Rotation> rot {current_node.rotation};
                    std::cout << "rotation: " << rot << std::endl;
                }
                print_cube(current_node.cube);
                std::cout << std::endl;
                Cube check(cube);
                std::vector<Cube::Rotation> res_rotations;
                for (uint8_t i = 0; i <= max_depth; ++i) {
                    if (rotations[i] != Cube::Rotation::None) {
                        res_rotations.push_back(rotations[i]);
                    }
                }
                print_cube(check.ApplyRotations(res_rotations));
                std::cout << "BBBB" << std::endl;
        /////////////////////////////////////////
    }

    std::vector<Cube::Rotation> res_rotations;
    for (uint8_t i = 0; i <= max_depth; ++i) {
        if (rotations[i] != Cube::Rotation::None) {
            res_rotations.push_back(rotations[i]);
        }
    }

    return res_rotations;
}
