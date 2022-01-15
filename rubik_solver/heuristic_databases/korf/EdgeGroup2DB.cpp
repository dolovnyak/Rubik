#include "EdgeGroup2DB.hpp"

/// There are 12! / (12 - 7)! * 2^7 permutations with orientations.
/// (7 cubies occupying 12 positions in a group, and each cubie can be in 1 of 2 states).
/// Each permutation is reachable in 11 moves or fewer, so each move can be stored in 4 bits.
/// That gives 12! / (12 - 7)! * 2^7 / 2 / 1024 / 1024 (~244MB).
EdgeGroup2DB::EdgeGroup2DB() : HeuristicDB(510935040) {}

size_t EdgeGroup2DB::GenerateDbIndexByCube(const Cube& cube) const {
    std::array<uint8_t, kEdgesGroup2Number> edges_permutation{};
    std::array<uint8_t, kEdgesGroup2Number> edges_orientation{};

    /// For each edge we check it's current edge_index.
    /// And we store only edge_indexes from 5 to 11.
    int received_edges = 0;
    for (uint8_t current_edge_i = 0; current_edge_i < kEdgesNumber && received_edges != 7; ++current_edge_i) {
        Cube::Edge current_edge = kAllEdges[current_edge_i];
        uint8_t current_edge_stored_index = cube.GetEdgeIndex(current_edge);

        if (current_edge_stored_index > 4) {
            edges_permutation[current_edge_stored_index] = current_edge_i;
            edges_orientation[current_edge_stored_index] = cube.GetEdgeOrientation(current_edge);
            ++received_edges;
        }
    }

    size_t rank = _permutation_rank_maker.rank(edges_permutation);

    /// Treat the orientations as a base-2 number, and convert it to base-10.
    size_t edges_orientation_to_number =
            edges_orientation[0] * 64 +
            edges_orientation[1] * 32 +
            edges_orientation[2] * 16 +
            edges_orientation[3] * 8 +
            edges_orientation[4] * 4 +
            edges_orientation[5] * 2 +
            edges_orientation[6];

    // Combine the permutation and orientation into a single index. p * 2^7 + o
    return rank * 128 + edges_orientation_to_number;
}
