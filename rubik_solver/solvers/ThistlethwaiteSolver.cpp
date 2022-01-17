#include "ThistlethwaiteSolver.hpp"

void ThistlethwaiteSolver::InitHeuristics() {
    LOG_INFO("Init Thistlethwaite heuristic databases");
    _thistlethwaite_heuristics.InitAllDB();
    LOG_INFO("Init Thistlethwaite heuristic databases SUCCESS");
}

std::vector<Cube::Rotation> ThistlethwaiteSolver::Solve() {
    throw std::logic_error("ThistlethwaiteSolver Solve not implemented");
}
