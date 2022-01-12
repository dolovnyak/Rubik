#pragma once

#include <cstdint>
#include <vector>
#include "CornerDB.hpp"
#include "EdgeGroup1DB.hpp"
#include "EdgeGroup2DB.hpp"
#include "EdgePermutationsDB.hpp"
#include "korf_defenitions.hpp"

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
