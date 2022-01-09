#pragma once

#include "Solver.hpp"
#include "KorfHeuristicDB.hpp"

class KorfSolver : public Solver {
 public:
    KorfSolver();

    bool ParseHeuristicsDB() override;
    void GenerateHeuristicsDB() override;
    void WriteToFileHeuristicsDB() override;

 private:
    KorfHeuristicDB corner_db;
};
