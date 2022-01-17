#pragma once

#include "HeuristicDB.hpp"
#include "cube_defenitions.hpp"
#include "CombinationRankMaker.hpp"

/// Second step in thistlethwaite algorithm.
class CornerOrientationsPlus4EdgePermutationsDB : public HeuristicDB {
public:
    CornerOrientationsPlus4EdgePermutationsDB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const override;

 private:
    CombinationRankMaker<kEdgesNumber, 4> _combination_rank_maker;
};
