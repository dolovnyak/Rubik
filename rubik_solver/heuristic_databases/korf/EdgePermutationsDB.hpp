#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

/// There are 12 edges, so 12! possible permutations.
/// Each permutation is reachable in 10 moves or fewer, so each move can be stored in 4 bits.
/// That gives 12! / 2 / 1024 / 1024 (~228MB).
static constexpr size_t kEdgePermutationsDbSize = 479001600;

/// This db contains only permutations of the 12 edges.
class EdgePermutationsDB {
 public:
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const;

 private:
    PermutationRankMaker<kEdgesNumber> _permutation_rank_maker;
};
