#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "korf_defenitions.hpp"

/// This db contains only permutations of the 12 edges.
class EdgePermutationsDB : public HeuristicDB {
public:
    EdgePermutationsDB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube &cube) const override;

private:
    PermutationRankMaker<kEdgesNumber> _permutation_rank_maker;
};
