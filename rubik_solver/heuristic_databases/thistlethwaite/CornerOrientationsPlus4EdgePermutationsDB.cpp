#include "CornerOrientationsPlus4EdgePermutationsDB.hpp"

/// For the four edges, there are 12! / (4! * (12 - 4)!) combinations:
/// 4 edges by 12 positions, and we don't need edges permutations.
/// There are 8 corners, and the orientations of 7 dictate the orientation of the 8th
/// Corners have three possible orientations, so there are 3^7 corner orientation permutations.
/// Total: 12C4 * 3^7 / 1024^2 / 2 = 1082565 / 1024 / 2 = ~528.60 KB on disk.

CornerOrientationsPlus4EdgePermutationsDB::CornerOrientationsPlus4EdgePermutationsDB() : HeuristicDB(1082565) {}

size_t CornerOrientationsPlus4EdgePermutationsDB::GenerateDbIndexByCube(const Cube& cube) const {
    std::array<uint8_t, 4> edge_combination{};

    unsigned combination_index = 0;
    for (uint8_t current_edge_i = 0; current_edge_i < kEdgesNumber && combination_index < 4; ++current_edge_i) {
        Cube::Edge stored_edge = static_cast<Cube::Edge>(cube.GetEdgeIndex(kAllEdges[current_edge_i]));

        if (stored_edge == Cube::Edge::FR || stored_edge == Cube::Edge::FL ||
            stored_edge == Cube::Edge::BL || stored_edge == Cube::Edge::BR) {
            edge_combination[combination_index] = current_edge_i;
            ++combination_index;
        }
    }

    uint32_t rank = _permutation_rank_maker.rank(edge_combination);

    std::array<uint8_t, 7> corner_orientations = {
            cube.GetCornerOrientation(Cube::Corner::ULB),
            cube.GetCornerOrientation(Cube::Corner::URB),
            cube.GetCornerOrientation(Cube::Corner::URF),
            cube.GetCornerOrientation(Cube::Corner::ULF),
            cube.GetCornerOrientation(Cube::Corner::DLF),
            cube.GetCornerOrientation(Cube::Corner::DLB),
            cube.GetCornerOrientation(Cube::Corner::DRB)
            };

    /// Treat the orientations as a base-3 number, and convert it to base-10.
    /// 7 corner orientations dictate the orientation of the 8th, so only 7 need to be stored.
    uint32_t orientation_number =
            corner_orientations[0] * 729 +
            corner_orientations[1] * 243 +
            corner_orientations[2] * 81 +
            corner_orientations[3] * 27 +
            corner_orientations[4] * 9 +
            corner_orientations[5] * 3 +
            corner_orientations[6];

    /// Combine four edge rank and corner orientation number (3^7 == 2187).
    return rank * 2187 + orientation_number;
}
