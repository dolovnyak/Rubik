#pragma once

#include "KorfHeuristicDB.hpp"
#include "logs.hpp"
#include "find_solve_through_ida_star.hpp"

class KorfSolver {
 public:
    void InitHeuristics();

    std::vector<Cube::Rotation> Solve(Cube cube);

 private:
//    KorfHeuristicDB _korf_heuristics;
};
