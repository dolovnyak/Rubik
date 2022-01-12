#pragma once

#include "Solver.hpp"

class ThistlethwaiteSolver : public Solver {
 public:
    ~ThistlethwaiteSolver() override = default;

    void InitHeuristics() override;
    std::vector<Cube::Rotation> Solve() override;
};
