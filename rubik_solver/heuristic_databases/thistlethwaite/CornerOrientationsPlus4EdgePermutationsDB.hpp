#pragma once

#include "cube_defenitions.hpp"
#include "CombinationRankMaker.hpp"

/// For the four edges, there are 12! / (4! * (12 - 4)!) combinations:
/// 4 edges by 12 positions, and we don't need edges permutations.
/// There are 8 corners, and the orientations of 7 dictate the orientation of the 8th
/// Corners have three possible orientations, so there are 3^7 corner orientation permutations.
/// Total: 12C4 * 3^7 / 1024^2 / 2 = 1082565 / 1024 / 2 = ~528.60 KB on disk.
static constexpr size_t kThistlethwaiteStep2DbSize = 1082565;

static constexpr std::array<Cube::Rotation, 14> kThistlethwaiteStep2Rotations = {
        Cube::Rotation::R,
        Cube::Rotation::OppositeR,
        Cube::Rotation::R2,
        Cube::Rotation::L,
        Cube::Rotation::OppositeL,
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


/// Step 2 db in thistlethwaite algorithm.
class CornerOrientationsPlus4EdgePermutationsDB {
public:
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const;

 private:
    CombinationRankMaker<kEdgesNumber, 4> _combination_rank_maker;
};
