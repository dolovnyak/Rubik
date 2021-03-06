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

std::vector<Cube::Rotation> ToRotationsArray(const std::string& value) {
    std::vector<Cube::Rotation> res;

    if (value.empty()) {
        return res;
    }

    size_t first = 0;
    size_t second;
    while (true) {
        if (value[first] == ' ') {
            ++first;
            continue;
        }
        if (first >= value.size()) {
            return res;
        }
        second = first;
        while (value[second] != ' ' && second < value.size()) {
            ++second;
        }

        std::string current_arg = value.substr(first, second - first);
        auto rotation_it = kStringToRotationMap.find(current_arg);
        if (rotation_it == kStringToRotationMap.end()) {
            throw std::runtime_error("invalid input in \"" + current_arg + "\"");
        }
        res.push_back(rotation_it->second);

        first = second;
    }
}

template<class Solver>
void SolverProcessing(Solver solver, Cube cube) {
    solver.InitHeuristics();
    std::vector<Cube::Rotation> solve_rotations = solver.Solve(cube);
    std::cout << solve_rotations << std::endl;
//    cube.ApplyRotations(solve_rotations);
//    print_cube(cube);
}

}

int main(int argc, char **argv) {
    argparse::ArgumentParser argparse("rubik-solver");

    argparse.add_argument("cube_rotations")
            .required()
            .help("queue of cube rotations.");

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
        std::string string_rotations = argparse.get<std::string>("cube_rotations");
        std::vector rotations = ToRotationsArray(string_rotations);
        if (rotations.empty()) {
            exit(0);
        }
        Cube cube;
        cube.ApplyRotations(rotations);

        Algorithm algorithm = argparse.get<Algorithm>("-a");
        LOG_INFO("Processing Algorithm: ", algorithm);

        switch (algorithm) {
            case Algorithm::Thistlethwaite:
                SolverProcessing(ThistlethwaiteSolver(), std::move(cube)); break;
            case Algorithm::Korf:
                SolverProcessing(KorfSolver(), std::move(cube)); break;
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR(e.what());
    }
    exit(0);
}
