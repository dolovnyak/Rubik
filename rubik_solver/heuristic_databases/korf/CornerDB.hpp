#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

/// This DB contains all corners permutations with orientations
class CornerDB : public HeuristicDB {
public:
    CornerDB();
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube &cube) const override;

private:
    PermutationRankMaker<kCornersNumber> permutation_rank_maker;
};
