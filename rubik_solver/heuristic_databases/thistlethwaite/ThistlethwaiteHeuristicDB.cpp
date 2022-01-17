#include "ThistlethwaiteHeuristicDB.hpp"
#include "generate_db_through_bfs.hpp"

void ThistlethwaiteHeuristicDB::InitAllDB() {
    LOG_INFO("Try parse edge_orientations (step1) db");
    if (!_step1_db.ParseDbFromFile(kStep1DbPath)) {
        LOG_INFO("Parse failed, start edge_orientations db generation");
        generate_db_through_bfs(&_step1_db);
        LOG_INFO("Start writing edge_orientations db");
        _step1_db.WriteDbToFile(kStep1DbPath);
    }
    LOG_INFO("Init edge_orientations (step1) db SUCCESS");

    LOG_INFO("Try parse corner_orientations_plus_4_edge_permutations (step2) db");
    if (!_step2_db.ParseDbFromFile(kStep2DbPath)) {
        LOG_INFO("Parse failed, start corner_orientations_plus_4_edge_permutations db generation");
        generate_db_through_bfs(&_step2_db);
        LOG_INFO("Start writing corner_orientations_plus_4_edge_permutations db");
        _step2_db.WriteDbToFile(kStep2DbPath);
    }
    LOG_INFO("Init corner_orientations_plus_4_edge_permutations (step2) db SUCCESS");

    LOG_INFO("Try parse tetrad_paired_plus_4_edge_permutations (step3) db");
    if (!_step3_db.ParseDbFromFile(kStep3DbPath)) {
        LOG_INFO("Parse failed, start tetrad_paired_plus_4_edge_permutations db generation");
        generate_db_through_bfs(&_step3_db);
        LOG_INFO("Start writing tetrad_paired_plus_4_edge_permutations db");
        _step3_db.WriteDbToFile(kStep3DbPath);
    }
    LOG_INFO("Init tetrad_paired_plus_4_edge_permutations (step3) db SUCCESS");
}
