#pragma once

#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "cube_defenitions.hpp"

class CornerOrientationsPlus4EdgePermutationsDB : HeuristicDB {
    CornerOrientationsPlus4EdgePermutationsDB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const override;

 private:
    PermutationRankMaker<kEdgesNumber, 4> _permutation_rank_maker;
};
