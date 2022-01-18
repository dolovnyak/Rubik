#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

/// There are 12! / (12 - 7)! * 2^7 permutations with orientations.
/// (7 cubies occupying 12 positions in a group, and each cubie can be in 1 of 2 states).
/// Each permutation is reachable in 11 moves or fewer, so each move can be stored in 4 bits.
/// That gives 12! / (12 - 7)! * 2^7 / 2 / 1024 / 1024 (~244MB).
static constexpr size_t kEdgesGroup1DbSize = 510935040;

static constexpr int kEdgesGroup1Number = 7;

/// This database contains 7 of the 12 edges permutations with orientations.
/// The 7 edges are UB, UR, UF, UL, FR, FL, and BL.
class EdgeGroup1DB {
 public:
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const;

 private:
    PermutationRankMaker<kEdgesNumber, kEdgesGroup1Number> _permutation_rank_maker;
};
