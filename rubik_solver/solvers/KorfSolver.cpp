#include "KorfSolver.hpp"

KorfSolver::KorfSolver() {}

void KorfSolver::InitHeuristics() {
    LOG_INFO("Init Korf heuristic databases");
    _korf_heuristics.InitAllDB();
    LOG_INFO("Init Korf heuristic databases SUCCESS");
}

std::vector<Cube::Rotation> KorfSolver::Solve() {
    throw std::logic_error("KorfSolver Solve not implemented");
}
