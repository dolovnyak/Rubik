#pragma once

#include "ThistlethwaiteHeuristicDB.hpp"
#include "find_solve_through_ida_star.hpp"

class ThistlethwaiteSolver {
 public:
    void InitHeuristics();

    std::vector<Cube::Rotation> Solve(Cube cube);

private:
    ThistlethwaiteHeuristicDB _thistlethwaite_heuristics;
};
