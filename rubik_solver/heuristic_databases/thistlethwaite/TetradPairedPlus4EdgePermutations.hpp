#pragma once

#include "HeuristicDB.hpp"
#include "cube_defenitions.hpp"

class TetradPairedPlus4EdgePermutations : HeuristicDB {

    TetradPairedPlus4EdgePermutations();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const override;
};
