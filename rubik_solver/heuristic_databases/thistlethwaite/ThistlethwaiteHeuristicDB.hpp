#pragma once

#include "EdgeOrientationsDB.hpp"
#include "CornerOrientationsPlus4EdgePermutationsDB.hpp"
#include "TetradPairedPlus4EdgePermutationsDB.hpp"
#include "logs.hpp"

constexpr std::string_view kStep1DbPath = "heuristic_databases/raw_databases/step1.db";
constexpr std::string_view kStep2DbPath = "heuristic_databases/raw_databases/step2.db";
constexpr std::string_view kStep3DbPath = "heuristic_databases/raw_databases/step3.db";
constexpr std::string_view kStep4DbPath = "heuristic_databases/raw_databases/step4.db";

class ThistlethwaiteHeuristicDB {
public:
    void InitAllDB();

private:
    EdgeOrientationsDB _step1_db;
    CornerOrientationsPlus4EdgePermutationsDB _step2_db;
    TetradPairedPlus4EdgePermutationsDB _step3_db;
};
