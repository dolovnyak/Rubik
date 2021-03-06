#include "CornerOrientationsPlus4EdgePermutationsDB.hpp"

[[nodiscard]] size_t CornerOrientationsPlus4EdgePermutationsDB::GenerateDbIndexByCube(const Cube& cube) const {
    std::array<uint8_t, 4> edge_combination{};
    size_t combination_index = 0;

    for (size_t current_edge_i = 0; current_edge_i < kEdgesNumber && combination_index < 4; ++current_edge_i) {
        Cube::Edge stored_edge = kAllEdges[cube.GetEdgeIndex(kAllEdges[current_edge_i])];

        if (stored_edge == Cube::Edge::FR || stored_edge == Cube::Edge::FL ||
            stored_edge == Cube::Edge::BL || stored_edge == Cube::Edge::BR) {
            edge_combination[combination_index] = current_edge_i;
            ++combination_index;
        }
    }
    size_t rank = _combination_rank_maker.rank(edge_combination);

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
    size_t orientation_number =
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
