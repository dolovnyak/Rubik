#include "EdgePermutationsDB.hpp"

/// There are 12 edges, so 12! possible permutations.
/// Each permutation is reachable in 10 moves or fewer, so each move can be stored in 4 bits.
/// That gives 12! / 2 / 1024 / 1024 (~228MB).
EdgePermutationsDB::EdgePermutationsDB() : HeuristicDB(479001600) {}

size_t EdgePermutationsDB::GenerateDbIndexByCube(const Cube& cube) const {
    std::array<uint8_t, kEdgesNumber> edges_permutation = {
            cube.GetEdgeIndex(Cube::Edge::UB),
            cube.GetEdgeIndex(Cube::Edge::UR),
            cube.GetEdgeIndex(Cube::Edge::UF),
            cube.GetEdgeIndex(Cube::Edge::UL),
            cube.GetEdgeIndex(Cube::Edge::FR),
            cube.GetEdgeIndex(Cube::Edge::FL),
            cube.GetEdgeIndex(Cube::Edge::BL),
            cube.GetEdgeIndex(Cube::Edge::BR),
            cube.GetEdgeIndex(Cube::Edge::DF),
            cube.GetEdgeIndex(Cube::Edge::DL),
            cube.GetEdgeIndex(Cube::Edge::DB),
            cube.GetEdgeIndex(Cube::Edge::DR)
    };

    return _permutation_rank_maker.rank(edges_permutation);
}
