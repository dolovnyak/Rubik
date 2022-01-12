#pragma once

#include "Solver.hpp"
#include "KorfHeuristicDB.hpp"
#include "generate_db_through_bfs.hpp"

class KorfSolver : public Solver {
 public:
    KorfSolver();

    void InitHeuristics() override;
    std::vector<Cube::Rotation> Solve() override;

 private:
    KorfHeuristicDB _korf_heuristics;
};
