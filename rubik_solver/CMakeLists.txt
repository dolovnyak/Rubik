cmake_minimum_required(VERSION 3.15)
project(rubik-solver)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        main.cpp
        cube/Cube.cpp
        solvers/KorfSolver.cpp
        solvers/ThistlethwaiteSolver.cpp
        heuristic_databases/korf/KorfHeuristicDB.cpp
        heuristic_databases/korf/EdgeGroup1DB.cpp
        heuristic_databases/korf/EdgeGroup2DB.cpp
        heuristic_databases/korf/EdgePermutationsDB.cpp
        heuristic_databases/korf/CornerDB.cpp
        heuristic_databases/thistlethwaite/CornerOrientationsPlus4EdgePermutationsDB.cpp
        heuristic_databases/thistlethwaite/EdgeOrientationsDB.cpp
        heuristic_databases/thistlethwaite/TetradPairedPlus4EdgePermutationsDB.cpp
        heuristic_databases/thistlethwaite/ThistlethwaiteHeuristicDB.cpp
        utilities/UnorderedPairSetRankMaker.hpp
        utilities/CombinationRankMaker.hpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        utilities
        solvers
        cube
        heuristic_databases
        heuristic_databases/korf
        heuristic_databases/thistlethwaite
        )

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")
