#pragma once

#include "Solver.hpp"

class KorfSolver : public Solver {
 public:
    bool ParseHeuristicDatabases() override;
};
