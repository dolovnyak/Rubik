#pragma once

#include <ostream>

enum class SolverAlgorithm {
    Thistlethwaite = 0,
    Korf
};

std::ostream &operator<<(std::ostream &os, SolverAlgorithm algorithm);

class Solver {
 public:
    virtual bool ParseHeuristicDatabases() = 0;
};
