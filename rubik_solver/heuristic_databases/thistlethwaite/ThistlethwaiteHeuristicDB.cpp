#include "ThistlethwaiteHeuristicDB.hpp"

void ThistlethwaiteHeuristicDB::InitAllDB() {
    LOG_INFO("Try parse edge_orientations (step1) db");
    if (!step1_db.ParseDbFromFile(kStep1DbPath)) {
        LOG_INFO("Parse failed, start edge_orientations db generation");
        generate_db_through_bfs(&step1_db, kAllRotations);
        LOG_INFO("Start writing edge_orientations db");
        step1_db.WriteDbToFile(kStep1DbPath);
    }
    LOG_INFO("Init edge_orientations (step1) db SUCCESS");

    LOG_INFO("Try parse corner_orientations_plus_4_edge_permutations (step2) db");
    if (!step2_db.ParseDbFromFile(kStep2DbPath)) {
        LOG_INFO("Parse failed, start corner_orientations_plus_4_edge_permutations db generation");
        generate_db_through_bfs(&step2_db, kThistlethwaiteStep2Rotations);
        LOG_INFO("Start writing corner_orientations_plus_4_edge_permutations db");
        step2_db.WriteDbToFile(kStep2DbPath);
    }
    LOG_INFO("Init corner_orientations_plus_4_edge_permutations (step2) db SUCCESS");

    LOG_INFO("Try parse tetrad_paired_plus_4_edge_permutations (step3) db");
    if (!step3_db.ParseDbFromFile(kStep3DbPath)) {
        LOG_INFO("Parse failed, start tetrad_paired_plus_4_edge_permutations db generation");
        generate_db_through_bfs(&step3_db, kThistlethwaiteStep3Rotations);
        LOG_INFO("Start writing tetrad_paired_plus_4_edge_permutations db");
        step3_db.WriteDbToFile(kStep3DbPath);
    }
    LOG_INFO("Init tetrad_paired_plus_4_edge_permutations (step3) db SUCCESS");

    LOG_INFO("Init korf (step4) db");
    step4_db.InitAllDB();
    LOG_INFO("Init korf (step4) db SUCCESS");
}
