#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

constexpr int kEdgesGroup1Number = 7;

/// This database contains 7 of the 12 edges permutations with orientations.
/// The 7 edges are UB, UR, UF, UL, FR, FL, and BL.
class EdgeGroup1DB : public HeuristicDB {
 public:
    EdgeGroup1DB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const override;

 private:
    PermutationRankMaker<kEdgesNumber, kEdgesGroup1Number> _permutation_rank_maker;
};
