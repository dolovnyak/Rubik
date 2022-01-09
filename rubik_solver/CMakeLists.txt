cmake_minimum_required(VERSION 3.15)
project(rubik-solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        main.cpp
        cube/Cube.cpp
        solvers/Solver.cpp
        solvers/KorfSolver.cpp
        solvers/ThistlethwaiteSolver.cpp
        heuristic_databases/HeuristicDB.cpp
        heuristic_databases/Korf/KorfHeuristicDB.cpp
        heuristic_databases/db_generators/HeuristicsGenerator.cpp
        heuristic_databases/db_generators/KorfHeuristicsGenerator.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        utilities
        solvers
        cube
        heuristic_databases
        heuristic_databases/db_generators
        heuristic_databases/Korf
        )
