#pragma once

#include "HeuristicDB.hpp"

template <class Heuristic>
std::vector<Cube::Rotation> find_solve_through_ida_star(Heuristic heuristic, const Cube& cube) {
    std::cout << "heuristic: " << (int)heuristic.GetEstimatedMovesNumber(cube) << std::endl;
    return {};
}