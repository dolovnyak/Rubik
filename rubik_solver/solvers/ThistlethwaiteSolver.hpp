#pragma once

#include "Solver.hpp"
#include "ThistlethwaiteHeuristicDB.hpp"

class ThistlethwaiteSolver : public Solver {
 public:
    ~ThistlethwaiteSolver() override = default;

    void InitHeuristics() override;
    std::vector<Cube::Rotation> Solve() override;

private:
    ThistlethwaiteHeuristicDB _thistlethwaite_heuristics;
};
