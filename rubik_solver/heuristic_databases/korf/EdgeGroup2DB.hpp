#pragma once

#include <cstdint>
#include "HeuristicDB.hpp"
#include "PermutationRankMaker.h"
#include "korf_defenitions.hpp"

/// This database contains the other 7 of the 12 edges permutations with orientations.
/// The 7 edges are FL, BL, BR, DF, DL, DB, and DR.
class EdgeGroup2DB : public HeuristicDB {
public:
    EdgeGroup2DB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube &cube) const override;

private:
    PermutationRankMaker<kEdgesNumber, kEdgesSecondGroupNumber> _permutation_rank_maker;

    using Edge = Cube::Edge;
    static constexpr std::array<Cube::Edge, kEdgesSecondGroupNumber> _edges = {
            Edge::FL, Edge::BL, Edge::BR, Edge::DF, Edge::DL, Edge::DB, Edge::DR
    };
};
