#include "Solver.hpp"

std::ostream &operator<<(std::ostream &os, SolverAlgorithm algorithm) {
    switch (algorithm) {
        case SolverAlgorithm::Thistlethwaite: os << "Thistlethwaite"; break;
        case SolverAlgorithm::Korf: os << "Korf"; break;
    }
    return os;
}
