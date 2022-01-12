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

    [[nodiscard]] uint8_t GetEstimatedMovesNumber(const Cube &cube) const;

private:
    CornerDB _corner_db;
    EdgeGroup1DB _edge_first_group_db;
    EdgeGroup2DB _edge_second_group_db;
    EdgePermutationsDB _edge_permutations_db;
};
