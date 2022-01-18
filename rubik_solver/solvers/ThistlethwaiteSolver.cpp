#include "ThistlethwaiteSolver.hpp"

void ThistlethwaiteSolver::InitHeuristics() {
    LOG_INFO("Init Thistlethwaite heuristic databases");
    _thistlethwaite_heuristics.InitAllDB();
    LOG_INFO("Init Thistlethwaite heuristic databases SUCCESS");
}

std::vector<Cube::Rotation> ThistlethwaiteSolver::Solve(Cube cube) {
//    LOG_INFO("Thistlethwaite step1");
//    std::vector<Cube::Rotation> res = find_solve_through_ida_star(std::move(_thistlethwaite_heuristics.step1_db), cube);
//
//    LOG_INFO("Thistlethwaite step2");
//    res = find_solve_through_ida_star(std::move(_thistlethwaite_heuristics.step2_db), cube);
//
//    LOG_INFO("Thistlethwaite step3");
//    res = find_solve_through_ida_star(std::move(_thistlethwaite_heuristics.step3_db), cube);

//    return res;
    (void)cube;
    throw std::logic_error("aaa");
}
