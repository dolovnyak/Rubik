#pragma once

#include <ostream>
#include "logs.hpp"
#include "Cube.hpp"

enum class SolverAlgorithm {
    Thistlethwaite = 0,
    Korf
};

std::ostream& operator<<(std::ostream& os, SolverAlgorithm algorithm);

class Solver {
 public:
    virtual ~Solver() = default;

    virtual void InitHeuristics() = 0;

    virtual std::vector<Cube::Rotation> Solve() = 0;
};
