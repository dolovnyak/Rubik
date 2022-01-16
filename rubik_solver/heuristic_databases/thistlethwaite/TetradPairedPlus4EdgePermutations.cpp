#include "TetradPairedPlus4EdgePermutations.hpp"

namespace {

[[nodiscard]] std::array<uint8_t, 2> GetTetradPair(const Cube& cube, Cube::Corner corner1, Cube::Corner corner2) {
    std::array<uint8_t, 2> tetrad_pair{};
    uint8_t pair_index = 0;

    for (uint8_t current_corner_i = 0; current_corner_i < kCornersNumber && pair_index < 2; ++current_corner_i) {
        Cube::Corner stored_corner = static_cast<Cube::Corner>(cube.GetCornerIndex(kAllCorners[current_corner_i]));

        if (stored_corner == corner1 || stored_corner == corner2) {
            tetrad_pair[pair_index] = current_corner_i;
            ++pair_index;
        }
    }
    return tetrad_pair;
}

}

/// There are 8 corners, so there are 4 pairs of tetrad paired corner combinations.
/// The corners therefore need (8! / (6! * 2!)) * (6! / (4! * 2!)) * (4! / (2! * 2!) = 2520 elements.
///
/// For the four edges, there are 8C4 combinations:
/// 4 edges and 8 positions (the E-slice edges are positioned in G2), and the order does not matter.
///
/// The parity is also stored.
/// Parity of corners and edges is related - when the edge parity is even, the corner parity is even too.
/// This doubles the number of elements the last bit in the index is used for parity, 0 for even, 1 for odd.
/// 70 * 2520 * 2 / 1024^2 / 2 = 352800 / 1024^2 / 2 = ~.17MB on disk.
TetradPairedPlus4EdgePermutations::TetradPairedPlus4EdgePermutations() : HeuristicDB(352800) {}

size_t TetradPairedPlus4EdgePermutations::GenerateDbIndexByCube(const Cube& cube) const {
    std::array<std::array<uint8_t, 2>, 4> tetrad_pairs{};

    tetrad_pairs[0] = GetTetradPair(cube, Cube::Corner::ULB, Cube::Corner::URF);
    tetrad_pairs[1] = GetTetradPair(cube, Cube::Corner::DLF, Cube::Corner::DRB);
    tetrad_pairs[2] = GetTetradPair(cube, Cube::Corner::URB, Cube::Corner::ULF);
    tetrad_pairs[3] = GetTetradPair(cube, Cube::Corner::DLB, Cube::Corner::DRF);

    uint32_t pairs_rank = this->pairSetIndexer.rank(tetrad_pairs);

    /// We ignore edges we reached from previous step, because we don't use rotations which could broke it.
    std::array<uint8_t, 12> edges_without_e_slice{};

    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::UB)] = 0;
    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::UR)] = 1;
    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::UF)] = 2;
    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::UL)] = 3;
    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::DF)] = 4;
    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::DL)] = 5;
    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::DB)] = 6;
    edges_without_e_slice[static_cast<uint8_t>(Cube::Edge::DR)] = 7;

    std::array<uint8_t, 4> edge_combination{};
    unsigned edgeComboInd = 0;

    for (uint8_t i = 0; i < numEdges && edgeComboInd < 4; ++i)
    {
        uint8_t edgeInd = cube.getEdgeIndex((EDGE)i);

        if (
                edgeInd == (uint8_t)EDGE::UB ||
                edgeInd == (uint8_t)EDGE::UF ||
                edgeInd == (uint8_t)EDGE::DF ||
                edgeInd == (uint8_t)EDGE::DB
                )
            edge_combination[edgeComboInd++] = edges_without_e_slice[i];
    }

    uint32_t edgeRank = this->comboIndexer.rank(edge_combination);

    // Parity of the corners.  This uses the same logic as a bubble sort would
    // to count the number of swaps needed, but toggles a boolean back and
    // forth to keep track of whether the number of swaps required to sort the
    // array of corner indexes is even or odd.
    uint8_t parity = 0;

    for (uint8_t i = 0; i < numCorners; ++i)
        for (uint8_t j = i + 1; j < numCorners; ++j)
            parity ^= cube.getCornerIndex((CORNER)i) < cube.getCornerIndex((CORNER)j);

    // 2520 = 8C2*6C2*4C2.
    return (edgeRank * 2520 + pairs_rank) * 2 + parity;

}
