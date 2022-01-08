cmake_minimum_required(VERSION 3.15)
project(rubik-solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        main.cpp
        solvers/Solver.cpp
        solvers/KorfSolver.cpp
        solvers/ThistlethwaiteSolver.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        utilities
        solvers
        )
