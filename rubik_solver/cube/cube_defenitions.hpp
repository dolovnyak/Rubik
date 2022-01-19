#pragma once

#include "Cube.hpp"
#include <vector>
#include <iomanip>
#include <iostream>

constexpr int kEdgesNumber = 12;
constexpr int kCornersNumber = 8;
constexpr int kRotationsNumber = 18;

static constexpr std::array<Cube::Rotation, kRotationsNumber> kAllRotations = [] {
    std::array<Cube::Rotation, kRotationsNumber> rotations{};
    for (int i = 0; i < kRotationsNumber; ++i) {
        rotations[i] = static_cast<Cube::Rotation>(i);
    }
    return rotations;
}();

static constexpr std::array<Cube::Edge, kEdgesNumber> kAllEdges = [] {
    std::array<Cube::Edge, kEdgesNumber> edges{};
    for (int i = 0; i < kEdgesNumber; ++i) {
        edges[i] = static_cast<Cube::Edge>(i);
    }
    return edges;
}();

static constexpr std::array<Cube::Corner, kCornersNumber> kAllCorners = [] {
    std::array<Cube::Corner, kCornersNumber> corners{};
    for (int i = 0; i < kCornersNumber; ++i) {
        corners[i] = static_cast<Cube::Corner>(i);
    }
    return corners;
}();


static const std::unordered_map<std::string, Cube::Rotation> kStringToRotationMap = {
        {"L", Cube::Rotation::L},
        {"L'", Cube::Rotation::OppositeL},
        {"L2", Cube::Rotation::L2},

        {"R", Cube::Rotation::R},
        {"R'", Cube::Rotation::OppositeR},
        {"R2", Cube::Rotation::R2},

        {"U", Cube::Rotation::U},
        {"U'", Cube::Rotation::OppositeU},
        {"U2", Cube::Rotation::U2},

        {"D", Cube::Rotation::D},
        {"D'", Cube::Rotation::OppositeD},
        {"D2", Cube::Rotation::D2},

        {"F", Cube::Rotation::F},
        {"F'", Cube::Rotation::OppositeF},
        {"F2", Cube::Rotation::F2},

        {"B", Cube::Rotation::B},
        {"B'", Cube::Rotation::OppositeB},
        {"B2", Cube::Rotation::B2},
};

static const std::unordered_map<Cube::Rotation, std::string> kRotationsToStringMap = {
        {Cube::Rotation::L, "L"},
        {Cube::Rotation::OppositeL, "L'"},
        {Cube::Rotation::L2, "L2"},

        {Cube::Rotation::R, "R"},
        {Cube::Rotation::OppositeR, "R'"},
        {Cube::Rotation::R2, "R2"},

        {Cube::Rotation::U, "U"},
        {Cube::Rotation::OppositeU, "U'"},
        {Cube::Rotation::U2, "U2"},

        {Cube::Rotation::D, "D"},
        {Cube::Rotation::OppositeD, "D'"},
        {Cube::Rotation::D2, "D2"},

        {Cube::Rotation::F, "F"},
        {Cube::Rotation::OppositeF, "F'"},
        {Cube::Rotation::F2, "F2"},

        {Cube::Rotation::B, "B"},
        {Cube::Rotation::OppositeB, "B'"},
        {Cube::Rotation::B2, "B2"}
};

inline void print_cube(const Cube& cube) {
    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    std::cout << std::setfill(' ') << '\n';

    // Up face.
    for (unsigned row = 0; row < 3; ++ row) {
        std::cout << std::setw(8) << std::right;

        for (unsigned col = 0; col < 3; ++ col)
            std::cout << colors[(unsigned)cube.GetColor(Cube::Face::Up, row, col)] << ' ';
        std::cout << '\n';
    }
    std::cout << std::endl;

    // Left front, right, back.
    for (unsigned row = 0; row < 3; ++ row)
    {
        for (unsigned col = 0; col < 3; ++ col)
            std::cout << colors[(unsigned)cube.GetColor(Cube::Face::Left,  row, col)] << ' ';
        std::cout << ' ';

        for (unsigned col = 0; col < 3; ++ col)
            std::cout << colors[(unsigned)cube.GetColor(Cube::Face::Front, row, col)] << ' ';
        std::cout << ' ';

        for (unsigned col = 0; col < 3; ++ col)
            std::cout << colors[(unsigned)cube.GetColor(Cube::Face::Right, row, col)] << ' ';
        std::cout << ' ';

        for (unsigned col = 0; col < 3; ++ col)
            std::cout << colors[(unsigned)cube.GetColor(Cube::Face::Back,  row, col)] << ' ';
        std::cout << '\n';
    }
    std::cout << std::endl;

    // Down face.
    for (unsigned row = 0; row < 3; ++ row)
    {
        std::cout << std::setw(8) << std::right;

        for (unsigned col = 0; col < 3; ++ col)
            std::cout << colors[(unsigned)cube.GetColor(Cube::Face::Down, row, col)] << ' ';
        std::cout << '\n';
    }

    std::cout << std::endl;
}

inline std::ostream &operator<<(std::ostream &os, const std::vector<Cube::Rotation>& rotations) {
    for (auto rotation : rotations) {
        auto string_rotation = kRotationsToStringMap.find(rotation)->second;
        os << string_rotation << std::string(" ");
    }
    return os;
}
