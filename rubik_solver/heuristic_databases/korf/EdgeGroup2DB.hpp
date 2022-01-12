#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

const int kEdgesGroup2Number = 7;

/// This database contains the other 7 of the 12 edges permutations with orientations.
/// The 7 edges are FL, BL, BR, DF, DL, DB, and DR.
class EdgeGroup2DB : public HeuristicDB {
public:
    EdgeGroup2DB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube &cube) const override;

private:
    PermutationRankMaker<kEdgesNumber, kEdgesGroup2Number> _permutation_rank_maker;
};
