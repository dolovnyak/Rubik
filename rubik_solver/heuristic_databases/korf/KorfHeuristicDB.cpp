#include "KorfHeuristicDB.hpp"
#include "generate_db_through_bfs.hpp"
#include "cube_defenitions.hpp"

void KorfHeuristicDB::InitAllDB() {
    LOG_INFO("Try parse corner db");
    if (!_corner_db.ParseDbFromFile(kCornerDbPath)) {
        LOG_INFO("Parse failed, start corner db generation");
        generate_db_through_bfs(&_corner_db);
        LOG_INFO("Start writing corner db");
        _corner_db.WriteDbToFile(kCornerDbPath);
    }
    LOG_INFO("Init corner db SUCCESS");

    LOG_INFO("Try parse edge permutations db");
    if (!_edge_permutations_db.ParseDbFromFile(kEdgePermutationsDbPath)) {
        LOG_INFO("Parse failed, start edge permutations db generation");
        generate_db_through_bfs(&_edge_permutations_db);
        LOG_INFO("Start writing edge permutations db");
        _edge_permutations_db.WriteDbToFile(kEdgePermutationsDbPath);
    }
    LOG_INFO("Init edge permutations db SUCCESS");

    LOG_INFO("Try parse edge group1 db");
    if (!_edge_first_group_db.ParseDbFromFile(kEdgeGroup1DbPath)) {
        LOG_INFO("Parse failed, start edge group1 db generation");
        generate_db_through_bfs(&_edge_first_group_db);
        LOG_INFO("Start writing edge group1 db");
        _edge_first_group_db.WriteDbToFile(kEdgeGroup1DbPath);
    }
    LOG_INFO("Init edge group1 db SUCCESS");

    LOG_INFO("Try parse edge group2 db");
    if (!_edge_second_group_db.ParseDbFromFile(kEdgeGroup2DbPath)) {
        LOG_INFO("Parse failed, start edge group2 db generation");
        generate_db_through_bfs(&_edge_second_group_db);
        LOG_INFO("Start writing edge group2 db");
        _edge_second_group_db.WriteDbToFile(kEdgeGroup2DbPath);
    }
    LOG_INFO("Init edge group2 db SUCCESS");
}

/**
 * Get the estimated number of moves it would take to get from a cube cube
 * to a scrambled cube.  The estimate is the max of all the databases.
 */
uint8_t KorfHeuristicDB::GetEstimatedMovesNumber(const Cube& cube) const {
    uint8_t corner_moves;
    uint8_t edge_first_group_moves;
    uint8_t edge_second_group_moves;
    uint8_t edge_permutations_moves;

    corner_moves = _corner_db.GetEstimatedMovesNumber(cube);
    edge_first_group_moves = _edge_first_group_db.GetEstimatedMovesNumber(cube);
    edge_second_group_moves = _edge_second_group_db.GetEstimatedMovesNumber(cube);
    edge_permutations_moves = _edge_permutations_db.GetEstimatedMovesNumber(cube);

#ifndef _RELEASE
    if (corner_moves == 0xF || edge_first_group_moves == 0xF ||
        edge_second_group_moves == 0xF || edge_permutations_moves == 0xF) {
        throw std::logic_error("Fatal: Cube cube not indexed in one of the databases.");
    }
#endif

    return std::max({corner_moves, edge_first_group_moves,
                     edge_second_group_moves, edge_permutations_moves});
}
