#pragma once

#include "HeuristicDB.hpp"
#include "cube_defenitions.hpp"
#include "CombinationRankMaker.hpp"
#include "UnorderedPairSetRankMaker.hpp"

/// There are 8 corners, so there are 4 _pairs of tetrad paired corner combinations.
/// The corners therefore need (8! / (6! * 2!)) * (6! / (4! * 2!)) * (4! / (2! * 2!) = 2520 elements.
///
/// For the four edges, there are 8C4 combinations:
/// 4 edges and 8 positions (the E-slice edges are positioned in G2), and the order does not matter.
///
/// The parity is also stored.
/// Parity of corners and edges is related - when the edge parity is even, the corner parity is even too.
/// This doubles the number of elements the last bit in the index is used for parity, 0 for even, 1 for odd.
/// 70 * 2520 * 2 / 1024^2 / 2 = 352800 / 1024^2 / 2 = ~.17MB on disk.
static constexpr size_t kThistlethwaiteStep3DbSize = 352800;

static constexpr std::array<Cube::Rotation, 10> kThistlethwaiteStep3Rotations = {
        Cube::Rotation::R2,
        Cube::Rotation::L2,
        Cube::Rotation::U,
        Cube::Rotation::OppositeU,
        Cube::Rotation::U2,
        Cube::Rotation::D,
        Cube::Rotation::OppositeD,
        Cube::Rotation::D2,
        Cube::Rotation::F2,
        Cube::Rotation::B2,
};

/// Step 3 db in thistlethwaite algorithm.
class TetradPairedPlus4EdgePermutationsDB {
public:
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const;

private:
    CombinationRankMaker<8, 4> _combination_rank_maker;
    UnorderedPairSetRankMaker<8> unordered_pair_set_rank_maker;
};
