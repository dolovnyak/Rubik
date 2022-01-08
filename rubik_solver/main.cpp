#include "argparse.hpp"
#include "logs.hpp"
#include "KorfSolver.hpp"
#include "ThistlethwaiteSolver.hpp"
#include <algorithm>

namespace {

SolverAlgorithm GetAlgorithmType(const std::string& value) {
    std::string lowercase_value = value;
    std::transform(lowercase_value.begin(), lowercase_value.end(), lowercase_value.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    if (lowercase_value == "korf")
        return SolverAlgorithm::Korf;
    if (lowercase_value == "thistlethwaite")
        return SolverAlgorithm::Thistlethwaite;

    throw std::runtime_error("There is no algorithm with name " + value + ".");
}

using SolverAlgorithms = std::tuple<ThistlethwaiteSolver, KorfSolver>;

}

int main(int argc, char **argv) {
    argparse::ArgumentParser argparse("rubik-solver");

    // TODO make moves queue
    argparse.add_argument("cube_rotations")
            .default_value("")
            .help("queue of cube rotations.");

    argparse.add_argument("-a", "--algorithm")
            .default_value(SolverAlgorithm::Thistlethwaite)
            .help("specify the solver algorithm [korf, thistlethwaite].")
            .action([](const std::string &value) { return GetAlgorithmType(value); });

    try {
        argparse.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err) {
        LOG_WARNING(err.what());
        LOG_WARNING(argparse);
        exit(0);
    }

    try {
        SolverAlgorithms algorithms;
        Solver* solver;

        switch (argparse.get<SolverAlgorithm>("-a")) {
            case SolverAlgorithm::Thistlethwaite:
                solver = &std::get<ThistlethwaiteSolver>(algorithms); break;
            case SolverAlgorithm::Korf:
                solver = &std::get<KorfSolver>(algorithms); break;
        }

        if (!solver->ParseHeuristicDatabases()) {
            // TODO init databases
            // TODO pass databases to solver
            // TODO write databases to files
        }

        // TODO solve_moves_queue = solver->Solve();
        // TODO std::cout << solve_moves_queue << std::endl;
    }
    catch (const std::exception& e) {
        LOG_ERROR(e.what());
    }
    exit(0);
}

