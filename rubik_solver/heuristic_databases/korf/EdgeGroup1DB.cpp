#include "EdgeGroup1DB.hpp"

/// There are 12! / (12 - 7)! * 2^7 possible permutations with orientations.
/// (7 cubies occupying 12 positions in a group, and each cubie can be in 1 of 2 states).
/// Each permutation is reachable in 11 moves or fewer, so each move can be stored in 4 bits.
/// That gives 12! / (12 - 7)! * 2^7 / 2 / 1024 / 1024 (~244MB).
EdgeGroup1DB::EdgeGroup1DB() : HeuristicDB(510935040)
{}

size_t EdgeGroup1DB::GenerateDbIndexByCube(const Cube& cube) const {
    std::array<uint8_t, kEdgesFirstGroupNumber> edges_permutation{};
    std::array<uint8_t, kEdgesFirstGroupNumber> edges_orientation{};

    for (size_t i = 0; i < _edges.size(); ++i) {
        edges_permutation[i] = cube.GetEdgeIndex(_edges[i]);
        edges_orientation[i] = cube.GetEdgeOrientation(_edges[i]);
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
