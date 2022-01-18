#pragma once

#include "EdgeOrientationsDB.hpp"
#include "CornerOrientationsPlus4EdgePermutationsDB.hpp"
#include "TetradPairedPlus4EdgePermutationsDB.hpp"
#include "logs.hpp"
#include "HeuristicDB.hpp"
#include "generate_db_through_bfs.hpp"
#include "KorfHeuristicDB.hpp"

constexpr std::string_view kStep1DbPath = "heuristic_databases/raw_databases/step1.db";
constexpr std::string_view kStep2DbPath = "heuristic_databases/raw_databases/step2.db";
constexpr std::string_view kStep3DbPath = "heuristic_databases/raw_databases/step3.db";

class ThistlethwaiteHeuristicDB {
public:
    void InitAllDB();

    HeuristicDB<kThistlethwaiteStep1DbSize, EdgeOrientationsDB> step1_db;
    HeuristicDB<kThistlethwaiteStep2DbSize, CornerOrientationsPlus4EdgePermutationsDB> step2_db;
    HeuristicDB<kThistlethwaiteStep3DbSize, TetradPairedPlus4EdgePermutationsDB> step3_db;
    KorfHeuristicDB step4_db;
};
