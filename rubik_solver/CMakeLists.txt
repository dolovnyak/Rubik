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
        heuristic_databases/Korf/EdgeGroup1DB.cpp
        heuristic_databases/Korf/EdgeGroup2DB.cpp
        heuristic_databases/Korf/EdgePermutationsDB.cpp
        heuristic_databases/generate_db_through_bfs.cpp
        heuristic_databases/Korf/CornerDB.cpp heuristic_databases/Korf/korf_defenitions.hpp cube/cube_defenitions.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        utilities
        solvers
        cube
        heuristic_databases
        heuristic_databases/Korf
        )

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )