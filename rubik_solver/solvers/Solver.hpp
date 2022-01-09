#pragma once

#include <ostream>

enum class SolverAlgorithm {
    Thistlethwaite = 0,
    Korf
};

std::ostream &operator<<(std::ostream &os, SolverAlgorithm algorithm);

class Solver {
 public:
    virtual bool ParseHeuristicsDB() = 0;
    virtual void GenerateHeuristicsDB() = 0;
    virtual void WriteToFileHeuristicsDB() = 0;
};
