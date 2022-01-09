#pragma once

#include "Solver.hpp"

class ThistlethwaiteSolver : public Solver {
 public:
    bool ParseHeuristicsDB() override;
    void WriteToFileHeuristicsDB() override;
    void GenerateHeuristicsDB() override;
};
