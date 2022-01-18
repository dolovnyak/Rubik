#include <algorithm>
#include "argparse.hpp"
#include "logs.hpp"
#include "KorfSolver.hpp"
#include "ThistlethwaiteSolver.hpp"
#include "cube_defenitions.hpp"

namespace {

enum class Algorithm {
    Thistlethwaite = 0,
    Korf
};

std::ostream& operator<<(std::ostream& os, Algorithm algorithm) {
    switch (algorithm) {
        case Algorithm::Thistlethwaite:
            os << "Thistlethwaite";
            break;
        case Algorithm::Korf:
            os << "Korf";
            break;
    }
    return os;
}

Algorithm GetAlgorithmType(const std::string& value) {
    std::string lowercase_value = value;
    std::transform(lowercase_value.begin(), lowercase_value.end(), lowercase_value.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowercase_value == "korf")
        return Algorithm::Korf;
    if (lowercase_value == "thistlethwaite")
        return Algorithm::Thistlethwaite;

    throw std::runtime_error("There is no algorithm with name " + value + ".");
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

template<class Solver>
void SolverProcessing(Solver solver, Cube cube) {
    solver.InitHeuristics();
    std::vector<Cube::Rotation> solve_rotations = solver.Solve(std::move(cube));
    std::cout << solve_rotations << std::endl;
}

}

int main(int argc, char **argv) {
    argparse::ArgumentParser argparse("rubik-solver");

    argparse.add_argument("cube_rotations")
            .default_value(std::vector<Cube::Rotation>())
            .help("queue of cube rotations.")
            .action([](const std::string& value) { return ToRotationsArray(value); });

    argparse.add_argument("-a", "--algorithm")
            .default_value(Algorithm::Thistlethwaite)
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
        Algorithm algorithm = argparse.get<Algorithm>("-a");
        LOG_INFO("Processing Algorithm: ", algorithm);

        switch (algorithm) {
            case Algorithm::Thistlethwaite:
                SolverProcessing(ThistlethwaiteSolver(), Cube());
            case Algorithm::Korf:
                SolverProcessing(KorfSolver(), Cube());
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR(e.what());
    }
    exit(0);
}
