#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

/// There are 8!*3^7 possible corner permutations with orientation.
/// Each permutation is reachable in 11 moves or fewer, so each move can be stored in 4 bits.
/// That gives 8!*3^7 / 2 / 1024 / 1024 (~42MB).
static constexpr size_t kCornersDbSize = 88179840;

/// This DB contains all corners permutations with orientations
class CornerDB {
 public:
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const;

 private:
    PermutationRankMaker<kCornersNumber> permutation_rank_maker;
};
