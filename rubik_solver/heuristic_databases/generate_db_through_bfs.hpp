#pragma once

#include <queue>
#include "HeuristicDB.hpp"
#include "Cube.hpp"
#include "logs.hpp"
#include "cube_defenitions.hpp"

struct StateWithDepth {
    StateWithDepth(const Cube& cube, uint8_t depth)
    : cube(cube), depth(depth)
    {}

    Cube    cube;
    uint8_t depth{};
};

void generate_db_through_bfs(HeuristicDB *db);
