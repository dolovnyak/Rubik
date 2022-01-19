#pragma once

#include "HeuristicDB.hpp"

struct StateNode {
    StateNode(const Cube& cube, uint8_t depth, Cube::Rotation rotation)
            : cube(cube), depth(depth), rotation(rotation) {}

    Cube cube;
    uint8_t depth;
    Cube::Rotation rotation;
};

template<size_t MaxRotationsSize, class Heuristic, size_t RotationsSize>
std::vector<Cube::Rotation> find_solve_through_ida_star(
        Heuristic heuristic, const Cube& cube, std::array<Cube::Rotation, RotationsSize> possible_rotations) {
    std::queue<StateNode> nodes;
    std::array<Cube::Rotation, MaxRotationsSize> rotations;

    uint8_t current_optimal_estimate = 0xFF; /// just for don't match with next_optimal_estimate
    uint8_t next_optimal_estimate = heuristic.GetEstimatedMovesNumber(cube);
    uint8_t max_depth = 0;

    while (true) {
        if (nodes.empty()) {
            nodes.emplace(cube, 0, Cube::Rotation::None);

            if (current_optimal_estimate == next_optimal_estimate) {
                throw std::logic_error("Heuristic doesn't correct");
            }

            if (next_optimal_estimate == 0) {
                throw std::logic_error("next_optimal_estimate is 0");
            }
            current_optimal_estimate = next_optimal_estimate;
        }

        StateNode current_node = nodes.front();
        nodes.pop();

        if (max_depth < current_node.depth) {
            max_depth = current_node.depth;
        }
        rotations[current_node.depth] = current_node.rotation;

        /////////////////////////////////
        std::cout << "AAAA" << std::endl;
        std::vector<Cube::Rotation> rot {current_node.rotation};
        std::cout << "rotation: " << rot << std::endl;
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

        if (current_node.depth == current_optimal_estimate) {
            if (current_node.cube.IsSolved()) {
                print_cube(current_node.cube); break;
            }
            continue;
        }

        for (auto rotation : possible_rotations) {
            Cube new_cube_state = Cube::Rotate(current_node.cube, rotation);
            uint8_t dh = current_node.depth + 1 + heuristic.GetEstimatedMovesNumber(new_cube_state);
            if (dh <= current_optimal_estimate) {
                nodes.emplace(new_cube_state, current_node.depth + 1, rotation);
                if (dh < next_optimal_estimate) {
                    next_optimal_estimate = dh;
                }
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
