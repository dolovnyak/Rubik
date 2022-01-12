#pragma once

#include <cstdint>
#include <array>
#include <unordered_map>
#include <string>

class Cube {
public:
    enum class Face : uint8_t {
        Up, Left, Front, Right, Back, Down
    };
    enum class Color : uint8_t {
        White, Green, Red, Blue, Orange, Yellow
    };
    enum class Edge : uint8_t {
        UB, UR, UF, UL, FR, FL, BL, BR, DF, DL, DB, DR
    };
    enum class Corner : uint8_t {
        ULB, URB, URF, ULF, DLF, DLB, DRB, DRF
    };
    enum class Rotation : uint8_t {
        L, OppositeL, L2,
        R, OppositeR, R2,
        U, OppositeU, U2,
        D, OppositeD, D2,
        F, OppositeF, F2,
        B, OppositeB, B2,
    };

    [[nodiscard]] bool IsSolved() const;

    Cube& Rotate(Rotation rotation);
    static Cube Rotate(const Cube& cube, Rotation rotation);

    [[nodiscard]] uint8_t GetEdgeIndex(Edge edge) const;
    [[nodiscard]] uint8_t GetEdgeOrientation(Edge edge) const;
    [[nodiscard]] uint8_t GetCornerIndex(Corner corner) const;
    [[nodiscard]] uint8_t GetCornerOrientation(Corner corner) const;

    Cube &RotationU();
    Cube &OppositeRotationU();
    Cube &RotationU2();

    Cube &RotationL();
    Cube &OppositeRotationL();
    Cube &RotationL2();

    Cube &RotationF();
    Cube &OppositeRotationF();
    Cube &RotationF2();

    Cube &RotationR();
    Cube &OppositeRotationR();
    Cube &RotationR2();

    Cube &RotationB();
    Cube &OppositeRotationB();
    Cube &RotationB2();

    Cube &RotationD();
    Cube &OppositeRotationD();
    Cube &RotationD2();

private:
    struct Cubie {
        /// 0 - 11 for _edges, 0 - 7 for _corners.
        uint8_t index;
        /// 0 - 1 for _edges, 0 - 2 for _corners.
        uint8_t orientation;

        inline bool operator==(const Cubie& cubie) const {
            return index == cubie.index && orientation == cubie.orientation;
        }
    };

    static constexpr std::array<Cubie, 12> kSolvedEdges = [] {
        std::array<Cubie, 12> array{};
        for (int i = 0; i < 12; ++i) {
            array[i].index = i;
            array[i].orientation = 0;
        }
        return array;
    }();
    static constexpr std::array<Cubie, 8> kSolvedCorners = [] {
        std::array<Cubie, 8> array{};
        for (int i = 0; i < 8; ++i) {
            array[i].index = i;
            array[i].orientation = 0;
        }
        return array;
    }();

    std::array<Cubie, 12> _edges = kSolvedEdges;
    std::array<Cubie, 8> _corners = kSolvedCorners;
    std::array<Color, 6> _centers = {Color::Red, Color::Blue, Color::White, Color::Green, Color::Yellow, Color::Orange};

    inline void UpdateCornerOrientation(Cube::Corner index, uint8_t amount);

    inline void UpdateEdgeOrientation(Cube::Edge index);

};

