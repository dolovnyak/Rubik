#include "KorfSolver.hpp"
#include "cube_defenitions.hpp"

void KorfSolver::InitHeuristics() {
    LOG_INFO("Init Korf heuristic databases");
    _korf_heuristics.InitAllDB();
    LOG_INFO("Init Korf heuristic databases SUCCESS");
}

std::vector<Cube::Rotation> KorfSolver::Solve(const Cube& cube) {
    LOG_INFO("Start solve");
    return find_solve_through_ida_star<20>(std::move(_korf_heuristics), cube, kAllRotations);
}

