#include <algorithm>
#include "argparse.hpp"
#include "logs.hpp"
#include "KorfSolver.hpp"
#include "ThistlethwaiteSolver.hpp"
#include "cube_defenitions.hpp"

namespace {
    SolverAlgorithm GetAlgorithmType(const std::string& value) {
        std::string lowercase_value = value;
        std::transform(lowercase_value.begin(), lowercase_value.end(), lowercase_value.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (lowercase_value == "korf")
            return SolverAlgorithm::Korf;
        if (lowercase_value == "thistlethwaite")
            return SolverAlgorithm::Thistlethwaite;

        throw std::runtime_error("There is no algorithm with name " + value + ".");
    }

    std::shared_ptr<Solver> MakeSolverInstanceByAlgorithm(SolverAlgorithm solver_algorithm) {
        switch (solver_algorithm) {
            case SolverAlgorithm::Thistlethwaite:
                return std::make_shared<ThistlethwaiteSolver>();
            case SolverAlgorithm::Korf:
                return std::make_shared<KorfSolver>();
        }
    }

    std::vector<Cube::Rotation> ToRotationsArray(std::string value) {
        size_t i;
        std::vector<Cube::Rotation> res;

        while (true) {
            i = value.find(' ');

            auto rotation_it = kStringToRotationMap.find(value.substr(0, i));
            if (rotation_it == kStringToRotationMap.end()) {
                throw std::runtime_error("Rotation lexeme isn't correct\n"
                                         "Lexeme is: \"" + rotation_it->first + "\"");
            }
            res.push_back(rotation_it->second);
            value.erase(0, i + 1);

            if (i == std::string::npos) { return res; }
        }
    }
}

int main(int argc, char **argv) {
    argparse::ArgumentParser argparse("rubik-solver");

    argparse.add_argument("cube_rotations")
            .default_value(std::vector<Cube::Rotation>())
            .help("queue of cube rotations.")
            .action([](const std::string& value) { return ToRotationsArray(value); });

    argparse.add_argument("-a", "--algorithm")
            .default_value(SolverAlgorithm::Thistlethwaite)
            .help("specify the solver algorithm [korf, thistlethwaite].")
            .action([](const std::string& value) { return GetAlgorithmType(value); });

    try {
        argparse.parse_args(argc, argv);
    }
    catch (const std::exception& e) {
        LOG_WARNING(e.what());
        LOG_WARNING(argparse);
        exit(0);
    }

    LOG_INFO("Argparse finish.");

    try {
        SolverAlgorithm algorithm = argparse.get<SolverAlgorithm>("-a");
        LOG_INFO("Processing Algorithm: ", algorithm);

        std::shared_ptr<Solver> solver = MakeSolverInstanceByAlgorithm(algorithm);
        solver->InitHeuristics();
        std::vector<Cube::Rotation> solve_rotations = solver->Solve();
//        std::cout << solve_rotations << std::endl;
    }
    catch (const std::exception& e) {
        LOG_ERROR(e.what());
    }
    exit(0);
}
