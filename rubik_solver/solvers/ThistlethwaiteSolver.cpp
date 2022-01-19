#include "ThistlethwaiteSolver.hpp"

void ThistlethwaiteSolver::InitHeuristics() {
    LOG_INFO("Init Thistlethwaite heuristic databases");
    _thistlethwaite_heuristics.InitAllDB();
    LOG_INFO("Init Thistlethwaite heuristic databases SUCCESS");
}

bool step1_solve_checker(const Cube& cube) {
    const uint8_t disoriented = 1;

    // If any edge is disoriented, return false.
    for (uint8_t i = 0; i < kEdgesNumber; ++i) {
        if (cube.GetEdgeOrientation(kAllEdges[i]) == disoriented) { return false; }
    }
    return true;
}

bool step2_solve_checker(const Cube& cube) {
    const uint8_t oriented = 0;

    // If any corner is disoriented, return false.
    for (uint8_t i = 0; i < kCornersNumber; ++i) {
        if (cube.GetCornerOrientation(kAllCorners[i]) != oriented) { return false; }
    }

    // The 4 edges E-slice edges.
    const std::array<Cube::Edge, 4> edges = {Cube::Edge::FR, Cube::Edge::FL, Cube::Edge::BL, Cube::Edge::BR};

    for (unsigned i = 0; i < 4; ++i) {
        uint8_t edge_index = cube.GetEdgeIndex(edges[i]);

        // If any edge in the E slice is not an E-slice edge, return false.
        // (E.g. if the RW edge is in the FL position.)
        if (edge_index != (uint8_t) edges[0] && edge_index != (uint8_t) edges[1] &&
            edge_index != (uint8_t) edges[2] && edge_index != (uint8_t) edges[3]) {
            return false;
        }
    }

    return true;
}

bool step3_solve_checker(const Cube& cube) {
    uint8_t corner_index;

    // {ULB, URF} pair.
    corner_index = cube.GetCornerIndex(Cube::Corner::ULB);
    if (corner_index != (uint8_t) Cube::Corner::ULB && corner_index != (uint8_t) Cube::Corner::URF)
        return false;

    corner_index = cube.GetCornerIndex(Cube::Corner::URF);
    if (corner_index != (uint8_t) Cube::Corner::ULB && corner_index != (uint8_t) Cube::Corner::URF)
        return false;

    // {DLF, DRB} pair.
    corner_index = cube.GetCornerIndex(Cube::Corner::DLF);
    if (corner_index != (uint8_t) Cube::Corner::DLF && corner_index != (uint8_t) Cube::Corner::DRB)
        return false;

    corner_index = cube.GetCornerIndex(Cube::Corner::DRB);
    if (corner_index != (uint8_t) Cube::Corner::DLF && corner_index != (uint8_t) Cube::Corner::DRB)
        return false;

    // If three sets of corners are paired, the last ({DLB, DRF}) must be, too.

    // The 4 edges M-slice edges.
    const std::array<Cube::Edge, 4> edges = {Cube::Edge::UB, Cube::Edge::UF, Cube::Edge::DF, Cube::Edge::DB};

    for (unsigned i = 0; i < 4; ++i) {
        uint8_t edge_index = cube.GetEdgeIndex(edges[i]);

        // If any edge in the M slice is not an M-slice edge, return false.
        if (edge_index != static_cast<uint8_t>(edges[0]) &&
            edge_index != static_cast<uint8_t>(edges[1]) &&
            edge_index != static_cast<uint8_t>(edges[2]) &&
            edge_index != static_cast<uint8_t>(edges[3]))
            return false;
    }

    // Parity must be even.  See G3PatternDatabase.cpp for an explanation.
    uint8_t parity = 0;

    for (uint8_t i = 0; i < kCornersNumber; ++i)
        for (uint8_t j = i + 1; j < kCornersNumber; ++j)
            parity ^= cube.GetCornerIndex(kAllCorners[i]) < cube.GetCornerIndex(kAllCorners[j]);

    return parity == 0;
}

bool step4_solve_checker(const Cube& cube) {
    return cube.IsSolved();
}

std::vector<Cube::Rotation> ThistlethwaiteSolver::Solve(Cube cube) {
    std::vector<Cube::Rotation> res;

    LOG_INFO("Thistlethwaite step1");
    std::vector<Cube::Rotation> tmp_res = find_solve_through_ida_star<20>(
            std::move(_thistlethwaite_heuristics.step1_db), cube, kAllRotations, step1_solve_checker);
    cube.ApplyRotations(tmp_res);
    res.insert(res.end(), tmp_res.begin(), tmp_res.end());

    LOG_INFO("Thistlethwaite step2");
    tmp_res = find_solve_through_ida_star<20>(std::move(_thistlethwaite_heuristics.step2_db), cube,
                                              kThistlethwaiteStep2Rotations, step2_solve_checker);
    cube.ApplyRotations(tmp_res);
    res.insert(res.end(), tmp_res.begin(), tmp_res.end());

    LOG_INFO("Thistlethwaite step3");
    tmp_res = find_solve_through_ida_star<20>(std::move(_thistlethwaite_heuristics.step3_db), cube,
                                              kThistlethwaiteStep3Rotations, step3_solve_checker);
    cube.ApplyRotations(tmp_res);
    res.insert(res.end(), tmp_res.begin(), tmp_res.end());

    LOG_INFO("Thistlethwaite step4");
    tmp_res = find_solve_through_ida_star<20>(std::move(_thistlethwaite_heuristics.step4_db), cube,
                                           kThistlethwaiteStep4Rotations, step4_solve_checker);
    res.insert(res.end(), tmp_res.begin(), tmp_res.end());
    return res;
}
