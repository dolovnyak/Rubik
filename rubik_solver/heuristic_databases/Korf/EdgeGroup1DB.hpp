#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "korf_defenitions.hpp"

/// This database contains 7 of the 12 edges permutations with orientations.
/// The 7 edges are UB, UR, UF, UL, FR, FL, and BL.
class EdgeGroup1DB : public HeuristicDB {
public:
    EdgeGroup1DB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube &cube) const override;

private:
    PermutationRankMaker<kEdgesNumber, kEdgesFirstGroupNumber> _permutation_rank_maker;

    using Edge = Cube::Edge;
    static constexpr std::array<Cube::Edge, kEdgesFirstGroupNumber> _edges = {
            Edge::UB, Edge::UR, Edge::UF, Edge::UL, Edge::FR, Edge::FL, Edge::BL
    };
};
