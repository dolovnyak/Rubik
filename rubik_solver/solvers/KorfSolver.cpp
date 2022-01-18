#include "KorfSolver.hpp"

void KorfSolver::InitHeuristics() {
    LOG_INFO("Init Korf heuristic databases");
    _korf_heuristics.InitAllDB();
    LOG_INFO("Init Korf heuristic databases SUCCESS");
}

std::vector<Cube::Rotation> KorfSolver::Solve(const Cube& cube) {
    return find_solve_through_ida_star(std::move(_korf_heuristics), cube);
}

