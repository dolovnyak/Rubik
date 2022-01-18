#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

/// There are 12! / (12 - 7)! * 2^7 permutations with orientations.
/// (7 cubies occupying 12 positions in a group, and each cubie can be in 1 of 2 states).
/// Each permutation is reachable in 11 moves or fewer, so each move can be stored in 4 bits.
/// That gives 12! / (12 - 7)! * 2^7 / 2 / 1024 / 1024 (~244MB).
static constexpr size_t kEdgesGroup2DbSize = 510935040;

const int kEdgesGroup2Number = 7;

/// This database contains the other 7 of the 12 edges permutations with orientations.
/// The 7 edges are FL, BL, BR, DF, DL, DB, and DR.
class EdgeGroup2DB {
 public:
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const;

 private:
    PermutationRankMaker<kEdgesNumber, kEdgesGroup2Number> _permutation_rank_maker;
};
