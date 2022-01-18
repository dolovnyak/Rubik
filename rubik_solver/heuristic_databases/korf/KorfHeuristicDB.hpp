#pragma once

#include <cstdint>
#include <vector>
#include "CornerDB.hpp"
#include "EdgeGroup1DB.hpp"
#include "EdgeGroup2DB.hpp"
#include "EdgePermutationsDB.hpp"

constexpr std::string_view kCornerDbPath = "heuristic_databases/raw_databases/corners.db";
constexpr std::string_view kEdgeGroup1DbPath = "heuristic_databases/raw_databases/edge_first_group.db";
constexpr std::string_view kEdgeGroup2DbPath = "heuristic_databases/raw_databases/edge_second_group.db";
constexpr std::string_view kEdgePermutationsDbPath = "heuristic_databases/raw_databases/edge_permutations.db";

/// This is an aggregate class that combines all the pattern databases needed for Korf's algorithm.
class KorfHeuristicDB {
 public:
    void InitAllDB();

    [[nodiscard]] uint8_t GetEstimatedMovesNumber(const Cube& cube) const;

 private:
    HeuristicDB<kCornersDbSize, CornerDB> _corner_db;
    HeuristicDB<kEdgesGroup1DbSize, EdgeGroup1DB> _edge_group1_db;
    HeuristicDB<kEdgesGroup2DbSize, EdgeGroup2DB> _edge_group2_db;
    HeuristicDB<kEdgePermutationsDbSize, EdgePermutationsDB> _edge_permutations_db;
};
