#pragma once

#include "HeuristicDB.hpp"
#include "cube_defenitions.hpp"
#include "CombinationRankMaker.hpp"
#include "UnorderedPairSetRankMaker.hpp"

class TetradPairedPlus4EdgePermutationsDB : public HeuristicDB {
public:
    TetradPairedPlus4EdgePermutationsDB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const override;

private:
    CombinationRankMaker<8, 4> _combination_rank_maker;
    UnorderedPairSetRankMaker<8> unordered_pair_set_rank_maker;
};
