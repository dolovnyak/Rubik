#include "Cube.hpp"

///**
// * Get the edge colors at an index.
// */
//std::array<Cube::Color, 2> Cube::getEdgeColors(
//        Cube::Edge ind) const
//{
//    std::array<Color, 2> colors;
//
//    Cubie edge = _edges.at((unsigned)ind);
//
//    switch ((Edge)edge.index)
//    {
//        case Edge::UB:
//            colors[0] = Color::Red;
//            colors[1] = Color::Yellow;
//            break;
//
//        case Edge::UR:
//            colors[0] = Color::Red;
//            colors[1] = Color::Green;
//            break;
//
//        case Edge::UF:
//            colors[0] = Color::Red;
//            colors[1] = Color::White;
//            break;
//
//        case Edge::UL:
//            colors[0] = Color::Red;
//            colors[1] = Color::Blue;
//            break;
//
//        case Edge::FR:
//            colors[0] = Color::White;
//            colors[1] = Color::Green;
//            break;
//
//        case Edge::FL:
//            colors[0] = Color::White;
//            colors[1] = Color::Blue;
//            break;
//
//        case Edge::BL:
//            colors[0] = Color::Yellow;
//            colors[1] = Color::Blue;
//            break;
//
//        case Edge::BR:
//            colors[0] = Color::Yellow;
//            colors[1] = Color::Green;
//            break;
//
//        case Edge::DF:
//            colors[0] = Color::Orange;
//            colors[1] = Color::White;
//            break;
//
//        case Edge::DL:
//            colors[0] = Color::Orange;
//            colors[1] = Color::Blue;
//            break;
//
//        case Edge::DB:
//            colors[0] = Color::Orange;
//            colors[1] = Color::Yellow;
//            break;
//
//        case Edge::DR:
//            colors[0] = Color::Orange;
//            colors[1] = Color::Green;
//            break;
//    }
//
//    if (edge.orientation == 1)
//        std::swap(colors[0], colors[1]);
//
//    return colors;
//}
//
///**
// * Get the corner colors at an index.  Three colors are returns: U or D, L or
// * R, F or B (YXZ).
// */
//std::array<Cube::Color, 3> Cube::getCornerColors(
//        Cube::Corner ind) const
//{
//    std::array<Color, 3> colors;
//
//    Cubie corner = _corners.at((unsigned)ind);
//
//    unsigned i0, i1, i2;
//
//    // Red or orange on top.
//    if (corner.orientation == 0)
//    {
//        i0 = 0;
//        i1 = 1;
//        i2 = 2;
//
//        // A quarter turn of U or D std::swaps the two other colors.
//        if ((corner.index + (unsigned)ind) % 2 == 1)
//            std::swap(i1, i2);
//    }
//    else if (corner.orientation == 1)
//    {
//        i0 = 1;
//        i1 = 2;
//        i2 = 0;
//
//        if ((corner.index + (unsigned)ind) % 2 == 1)
//            std::swap(i0, i1);
//    }
//    else // if (corner.orientation == 2)
//    {
//        i0 = 2;
//        i1 = 0;
//        i2 = 1;
//
//        if ((corner.index + (unsigned)ind) % 2 == 1)
//            std::swap(i0, i2);
//    }
//
//    switch ((Corner)corner.index)
//    {
//        case Corner::ULB:
//            colors[i0] = Color::Red;
//            colors[i1] = Color::Blue;
//            colors[i2] = Color::Yellow;
//            break;
//
//        case Corner::URB:
//            colors[i0] = Color::Red;
//            colors[i1] = Color::Green;
//            colors[i2] = Color::Yellow;
//            break;
//
//        case Corner::URF:
//            colors[i0] = Color::Red;
//            colors[i1] = Color::Green;
//            colors[i2] = Color::White;
//            break;
//
//        case Corner::ULF:
//            colors[i0] = Color::Red;
//            colors[i1] = Color::Blue;
//            colors[i2] = Color::White;
//            break;
//
//        case Corner::DLF:
//            colors[i0] = Color::Orange;
//            colors[i1] = Color::Blue;
//            colors[i2] = Color::White;
//            break;
//
//        case Corner::DLB:
//            colors[i0] = Color::Orange;
//            colors[i1] = Color::Blue;
//            colors[i2] = Color::Yellow;
//            break;
//
//        case Corner::DRB:
//            colors[i0] = Color::Orange;
//            colors[i1] = Color::Green;
//            colors[i2] = Color::Yellow;
//            break;
//
//        case Corner::DRF:
//            colors[i0] = Color::Orange;
//            colors[i1] = Color::Green;
//            colors[i2] = Color::White;
//            break;
//    }
//
//    return colors;
//}
//
///**
// * Get the facet color using a face, row, and column.
// */
//Cube::Color Cube::getColor(
//        Face f, unsigned row, unsigned col) const
//{
//    if (row == 1 && col == 1)
//        return (Color)_centers[(unsigned)f];
//
//    // The colors are arranged Y, X, Z (see getCornerColors).
//    if (f == Face::Up)
//    {
//        if (row == 0)
//        {
//            if (col == 0)
//                return getCornerColors(Corner::ULB)[0];
//            else if (col == 1)
//                return getEdgeColors(Edge::UB)[0];
//            else
//                return getCornerColors(Corner::URB)[0];
//        }
//        else if (row == 1)
//        {
//            if (col == 0)
//                return getEdgeColors(Edge::UL)[0];
//            else
//                return getEdgeColors(Edge::UR)[0];
//        }
//        else
//        {
//            if (col == 0)
//                return getCornerColors(Corner::ULF)[0];
//            else if (col == 1)
//                return getEdgeColors(Edge::UF)[0];
//            else
//                return getCornerColors(Corner::URF)[0];
//        }
//    }
//    else if (f == Face::Left)
//    {
//        if (row == 0)
//        {
//            if (col == 0)
//                return getCornerColors(Corner::ULB)[1];
//            else if (col == 1)
//                return getEdgeColors(Edge::UL)[1];
//            else
//                return getCornerColors(Corner::ULF)[1];
//        }
//        else if (row == 1)
//        {
//            if (col == 0)
//                return getEdgeColors(Edge::BL)[1];
//            else
//                return getEdgeColors(Edge::FL)[1];
//        }
//        else
//        {
//            if (col == 0)
//                return getCornerColors(Corner::DLB)[1];
//            else if (col == 1)
//                return getEdgeColors(Edge::DL)[1];
//            else
//                return getCornerColors(Corner::DLF)[1];
//        }
//    }
//    else if (f == Face::Front)
//    {
//        if (row == 0)
//        {
//            if (col == 0)
//                return getCornerColors(Corner::ULF)[2];
//            else if (col == 1)
//                return getEdgeColors(Edge::UF)[1];
//            else
//                return getCornerColors(Corner::URF)[2];
//        }
//        else if (row == 1)
//        {
//            if (col == 0)
//                return getEdgeColors(Edge::FL)[0];
//            else
//                return getEdgeColors(Edge::FR)[0];
//        }
//        else
//        {
//            if (col == 0)
//                return getCornerColors(Corner::DLF)[2];
//            else if (col == 1)
//                return getEdgeColors(Edge::DF)[1];
//            else
//                return getCornerColors(Corner::DRF)[2];
//        }
//    }
//    else if (f == Face::Right)
//    {
//        if (row == 0)
//        {
//            if (col == 0)
//                return getCornerColors(Corner::URF)[1];
//            else if (col == 1)
//                return getEdgeColors(Edge::UR)[1];
//            else
//                return getCornerColors(Corner::URB)[1];
//        }
//        else if (row == 1)
//        {
//            if (col == 0)
//                return getEdgeColors(Edge::FR)[1];
//            else
//                return getEdgeColors(Edge::BR)[1];
//        }
//        else
//        {
//            if (col == 0)
//                return getCornerColors(Corner::DRF)[1];
//            else if (col == 1)
//                return getEdgeColors(Edge::DR)[1];
//            else
//                return getCornerColors(Corner::DRB)[1];
//        }
//    }
//    else if (f == Face::Back)
//    {
//        if (row == 0)
//        {
//            if (col == 0)
//                return getCornerColors(Corner::URB)[2];
//            else if (col == 1)
//                return getEdgeColors(Edge::UB)[1];
//            else
//                return getCornerColors(Corner::ULB)[2];
//        }
//        else if (row == 1)
//        {
//            if (col == 0)
//                return getEdgeColors(Edge::BR)[0];
//            else
//                return getEdgeColors(Edge::BL)[0];
//        }
//        else
//        {
//            if (col == 0)
//                return getCornerColors(Corner::DRB)[2];
//            else if (col == 1)
//                return getEdgeColors(Edge::DB)[1];
//            else
//                return getCornerColors(Corner::DLB)[2];
//        }
//    }
//    else // if (f == Face::Down)
//    {
//        if (row == 0)
//        {
//            if (col == 0)
//                return getCornerColors(Corner::DLF)[0];
//            else if (col == 1)
//                return getEdgeColors(Edge::DF)[0];
//            else
//                return getCornerColors(Corner::DRF)[0];
//        }
//        else if (row == 1)
//        {
//            if (col == 0)
//                return getEdgeColors(Edge::DL)[0];
//            else
//                return getEdgeColors(Edge::DR)[0];
//        }
//        else
//        {
//            if (col == 0)
//                return getCornerColors(Corner::DLB)[0];
//            else if (col == 1)
//                return getEdgeColors(Edge::DB)[0];
//            else
//                return getCornerColors(Corner::DRB)[0];
//        }
//    }
//}

uint8_t Cube::GetEdgeIndex(Edge edge) const {
    return _edges[static_cast<int>(edge)].index;
}

uint8_t Cube::GetEdgeOrientation(Edge edge) const {
    return _edges[static_cast<int>(edge)].orientation;
}

uint8_t Cube::GetCornerIndex(Corner corner) const {
    return _corners[static_cast<int>(corner)].index;
}

uint8_t Cube::GetCornerOrientation(Corner corner) const {
    return _corners[static_cast<int>(corner)].orientation;
}

bool Cube::IsSolved() const {
    return _corners == kSolvedCorners && _edges == kSolvedEdges;
}

inline void Cube::UpdateCornerOrientation(Corner index, uint8_t amount) {
    Cubie& corner = _corners[static_cast<uint8_t>(index)];
    corner.orientation = (corner.orientation + amount) % 3;
}

inline void Cube::UpdateEdgeOrientation(Edge index) {
    _edges[static_cast<uint8_t>(index)].orientation ^= 1;
}

Cube& Cube::RotationU() {
    Cubie tmp                       = _corners[(unsigned)Corner::ULF];
    _corners[(unsigned)Corner::ULF] = _corners[(unsigned)Corner::URF];
    _corners[(unsigned)Corner::URF] = _corners[(unsigned)Corner::URB];
    _corners[(unsigned)Corner::URB] = _corners[(unsigned)Corner::ULB];
    _corners[(unsigned)Corner::ULB] = tmp;

    tmp                             = _edges[(unsigned)Edge::UL];
    _edges[(unsigned)Edge::UL]      = _edges[(unsigned)Edge::UF];
    _edges[(unsigned)Edge::UF]      = _edges[(unsigned)Edge::UR];
    _edges[(unsigned)Edge::UR]      = _edges[(unsigned)Edge::UB];
    _edges[(unsigned)Edge::UB]      = tmp;

    return *this;
}

Cube& Cube::OppositeRotationU() {
    Cubie tmp                       = _corners[(unsigned)Corner::ULB];
    _corners[(unsigned)Corner::ULB] = _corners[(unsigned)Corner::URB];
    _corners[(unsigned)Corner::URB] = _corners[(unsigned)Corner::URF];
    _corners[(unsigned)Corner::URF] = _corners[(unsigned)Corner::ULF];
    _corners[(unsigned)Corner::ULF] = tmp;

    tmp                             = _edges[(unsigned)Edge::UB];
    _edges[(unsigned)Edge::UB]      = _edges[(unsigned)Edge::UR];
    _edges[(unsigned)Edge::UR]      = _edges[(unsigned)Edge::UF];
    _edges[(unsigned)Edge::UF]      = _edges[(unsigned)Edge::UL];
    _edges[(unsigned)Edge::UL]      = tmp;

    return *this;
}

Cube& Cube::RotationU2() {
    std::swap(_corners[(unsigned)Corner::ULB], _corners[(unsigned)Corner::URF]);
    std::swap(_corners[(unsigned)Corner::URB], _corners[(unsigned)Corner::ULF]);

    std::swap(_edges[(unsigned)Edge::UB], _edges[(unsigned)Edge::UF]);
    std::swap(_edges[(unsigned)Edge::UR], _edges[(unsigned)Edge::UL]);

    return *this;
}

Cube& Cube::RotationL() {
    Cubie tmp                       = _corners[(unsigned)Corner::DLB];
    _corners[(unsigned)Corner::DLB] = _corners[(unsigned)Corner::DLF];
    _corners[(unsigned)Corner::DLF] = _corners[(unsigned)Corner::ULF];
    _corners[(unsigned)Corner::ULF] = _corners[(unsigned)Corner::ULB];
    _corners[(unsigned)Corner::ULB] = tmp;

    tmp                             = _edges[(unsigned)Edge::BL];
    _edges[(unsigned)Edge::BL]      = _edges[(unsigned)Edge::DL];
    _edges[(unsigned)Edge::DL]      = _edges[(unsigned)Edge::FL];
    _edges[(unsigned)Edge::FL]      = _edges[(unsigned)Edge::UL];
    _edges[(unsigned)Edge::UL]      = tmp;

    UpdateCornerOrientation(Corner::DLB, 1);
    UpdateCornerOrientation(Corner::DLF, 2);
    UpdateCornerOrientation(Corner::ULF, 1);
    UpdateCornerOrientation(Corner::ULB, 2);

    return *this;
}

Cube& Cube::OppositeRotationL() {
    Cubie tmp                       = _corners[(unsigned)Corner::DLB];
    _corners[(unsigned)Corner::DLB] = _corners[(unsigned)Corner::ULB];
    _corners[(unsigned)Corner::ULB] = _corners[(unsigned)Corner::ULF];
    _corners[(unsigned)Corner::ULF] = _corners[(unsigned)Corner::DLF];
    _corners[(unsigned)Corner::DLF] = tmp;

    tmp                             = _edges[(unsigned)Edge::BL];
    _edges[(unsigned)Edge::BL]      = _edges[(unsigned)Edge::UL];
    _edges[(unsigned)Edge::UL]      = _edges[(unsigned)Edge::FL];
    _edges[(unsigned)Edge::FL]      = _edges[(unsigned)Edge::DL];
    _edges[(unsigned)Edge::DL]      = tmp;

    UpdateCornerOrientation(Corner::DLB, 1);
    UpdateCornerOrientation(Corner::DLF, 2);
    UpdateCornerOrientation(Corner::ULF, 1);
    UpdateCornerOrientation(Corner::ULB, 2);

    return *this;
}

Cube& Cube::RotationL2() {
    std::swap(_corners[(unsigned)Corner::DLB], _corners[(unsigned)Corner::ULF]);
    std::swap(_corners[(unsigned)Corner::ULB], _corners[(unsigned)Corner::DLF]);

    std::swap(_edges[(unsigned)Edge::BL], _edges[(unsigned)Edge::FL]);
    std::swap(_edges[(unsigned)Edge::UL], _edges[(unsigned)Edge::DL]);

    return *this;
}

Cube& Cube::RotationF() {
    Cubie tmp                       = _corners[(unsigned)Corner::ULF];
    _corners[(unsigned)Corner::ULF] = _corners[(unsigned)Corner::DLF];
    _corners[(unsigned)Corner::DLF] = _corners[(unsigned)Corner::DRF];
    _corners[(unsigned)Corner::DRF] = _corners[(unsigned)Corner::URF];
    _corners[(unsigned)Corner::URF] = tmp;

    tmp                             = _edges[(unsigned)Edge::UF];
    _edges[(unsigned)Edge::UF]      = _edges[(unsigned)Edge::FL];
    _edges[(unsigned)Edge::FL]      = _edges[(unsigned)Edge::DF];
    _edges[(unsigned)Edge::DF]      = _edges[(unsigned)Edge::FR];
    _edges[(unsigned)Edge::FR]      = tmp;

    UpdateCornerOrientation(Corner::ULF, 2);
    UpdateCornerOrientation(Corner::URF, 1);
    UpdateCornerOrientation(Corner::DRF, 2);
    UpdateCornerOrientation(Corner::DLF, 1);

    UpdateEdgeOrientation(Edge::UF);
    UpdateEdgeOrientation(Edge::FL);
    UpdateEdgeOrientation(Edge::DF);
    UpdateEdgeOrientation(Edge::FR);

    return *this;
}

Cube& Cube::OppositeRotationF() {
    Cubie tmp                       = _corners[(unsigned)Corner::ULF];
    _corners[(unsigned)Corner::ULF] = _corners[(unsigned)Corner::URF];
    _corners[(unsigned)Corner::URF] = _corners[(unsigned)Corner::DRF];
    _corners[(unsigned)Corner::DRF] = _corners[(unsigned)Corner::DLF];
    _corners[(unsigned)Corner::DLF] = tmp;

    tmp                             = _edges[(unsigned)Edge::UF];
    _edges[(unsigned)Edge::UF]      = _edges[(unsigned)Edge::FR];
    _edges[(unsigned)Edge::FR]      = _edges[(unsigned)Edge::DF];
    _edges[(unsigned)Edge::DF]      = _edges[(unsigned)Edge::FL];
    _edges[(unsigned)Edge::FL]      = tmp;

    UpdateCornerOrientation(Corner::ULF, 2);
    UpdateCornerOrientation(Corner::URF, 1);
    UpdateCornerOrientation(Corner::DRF, 2);
    UpdateCornerOrientation(Corner::DLF, 1);

    UpdateEdgeOrientation(Edge::UF);
    UpdateEdgeOrientation(Edge::FL);
    UpdateEdgeOrientation(Edge::DF);
    UpdateEdgeOrientation(Edge::FR);

    return *this;
}

Cube& Cube::RotationF2() {
    std::swap(_corners[(unsigned)Corner::ULF], _corners[(unsigned)Corner::DRF]);
    std::swap(_corners[(unsigned)Corner::URF], _corners[(unsigned)Corner::DLF]);

    std::swap(_edges[(unsigned)Edge::UF], _edges[(unsigned)Edge::DF]);
    std::swap(_edges[(unsigned)Edge::FL], _edges[(unsigned)Edge::FR]);

    return *this;
}

Cube& Cube::RotationR() {
    Cubie tmp                       = _corners[(unsigned)Corner::DRB];
    _corners[(unsigned)Corner::DRB] = _corners[(unsigned)Corner::URB];
    _corners[(unsigned)Corner::URB] = _corners[(unsigned)Corner::URF];
    _corners[(unsigned)Corner::URF] = _corners[(unsigned)Corner::DRF];
    _corners[(unsigned)Corner::DRF] = tmp;

    tmp                             = _edges[(unsigned)Edge::BR];
    _edges[(unsigned)Edge::BR]      = _edges[(unsigned)Edge::UR];
    _edges[(unsigned)Edge::UR]      = _edges[(unsigned)Edge::FR];
    _edges[(unsigned)Edge::FR]      = _edges[(unsigned)Edge::DR];
    _edges[(unsigned)Edge::DR]      = tmp;

    UpdateCornerOrientation(Corner::DRB, 2);
    UpdateCornerOrientation(Corner::DRF, 1);
    UpdateCornerOrientation(Corner::URF, 2);
    UpdateCornerOrientation(Corner::URB, 1);

    return *this;
}

Cube& Cube::OppositeRotationR() {
    Cubie tmp                       = _corners[(unsigned)Corner::DRB];
    _corners[(unsigned)Corner::DRB] = _corners[(unsigned)Corner::DRF];
    _corners[(unsigned)Corner::DRF] = _corners[(unsigned)Corner::URF];
    _corners[(unsigned)Corner::URF] = _corners[(unsigned)Corner::URB];
    _corners[(unsigned)Corner::URB] = tmp;

    tmp                             = _edges[(unsigned)Edge::BR];
    _edges[(unsigned)Edge::BR]      = _edges[(unsigned)Edge::DR];
    _edges[(unsigned)Edge::DR]      = _edges[(unsigned)Edge::FR];
    _edges[(unsigned)Edge::FR]      = _edges[(unsigned)Edge::UR];
    _edges[(unsigned)Edge::UR]      = tmp;

    UpdateCornerOrientation(Corner::DRB, 2);
    UpdateCornerOrientation(Corner::DRF, 1);
    UpdateCornerOrientation(Corner::URF, 2);
    UpdateCornerOrientation(Corner::URB, 1);

    return *this;
}

Cube& Cube::RotationR2() {
    std::swap(_corners[(unsigned)Corner::DRB], _corners[(unsigned)Corner::URF]);
    std::swap(_corners[(unsigned)Corner::URB], _corners[(unsigned)Corner::DRF]);

    std::swap(_edges[(unsigned)Edge::BR], _edges[(unsigned)Edge::FR]);
    std::swap(_edges[(unsigned)Edge::UR], _edges[(unsigned)Edge::DR]);

    return *this;
}

Cube& Cube::RotationB() {
    Cubie tmp                       = _corners[(unsigned)Corner::ULB];
    _corners[(unsigned)Corner::ULB] = _corners[(unsigned)Corner::URB];
    _corners[(unsigned)Corner::URB] = _corners[(unsigned)Corner::DRB];
    _corners[(unsigned)Corner::DRB] = _corners[(unsigned)Corner::DLB];
    _corners[(unsigned)Corner::DLB] = tmp;

    tmp                             = _edges[(unsigned)Edge::UB];
    _edges[(unsigned)Edge::UB]      = _edges[(unsigned)Edge::BR];
    _edges[(unsigned)Edge::BR]      = _edges[(unsigned)Edge::DB];
    _edges[(unsigned)Edge::DB]      = _edges[(unsigned)Edge::BL];
    _edges[(unsigned)Edge::BL]      = tmp;

    UpdateCornerOrientation(Corner::ULB, 1);
    UpdateCornerOrientation(Corner::URB, 2);
    UpdateCornerOrientation(Corner::DRB, 1);
    UpdateCornerOrientation(Corner::DLB, 2);

    UpdateEdgeOrientation(Edge::UB);
    UpdateEdgeOrientation(Edge::BL);
    UpdateEdgeOrientation(Edge::DB);
    UpdateEdgeOrientation(Edge::BR);

    return *this;
}

Cube& Cube::OppositeRotationB() {
    Cubie tmp                       = _corners[(unsigned)Corner::ULB];
    _corners[(unsigned)Corner::ULB] = _corners[(unsigned)Corner::DLB];
    _corners[(unsigned)Corner::DLB] = _corners[(unsigned)Corner::DRB];
    _corners[(unsigned)Corner::DRB] = _corners[(unsigned)Corner::URB];
    _corners[(unsigned)Corner::URB] = tmp;

    tmp                             = _edges[(unsigned)Edge::UB];
    _edges[(unsigned)Edge::UB]      = _edges[(unsigned)Edge::BL];
    _edges[(unsigned)Edge::BL]      = _edges[(unsigned)Edge::DB];
    _edges[(unsigned)Edge::DB]      = _edges[(unsigned)Edge::BR];
    _edges[(unsigned)Edge::BR]      = tmp;

    UpdateCornerOrientation(Corner::ULB, 1);
    UpdateCornerOrientation(Corner::URB, 2);
    UpdateCornerOrientation(Corner::DRB, 1);
    UpdateCornerOrientation(Corner::DLB, 2);

    UpdateEdgeOrientation(Edge::UB);
    UpdateEdgeOrientation(Edge::BL);
    UpdateEdgeOrientation(Edge::DB);
    UpdateEdgeOrientation(Edge::BR);

    return *this;
}

Cube& Cube::RotationB2() {
    std::swap(_corners[(unsigned)Corner::ULB], _corners[(unsigned)Corner::DRB]);
    std::swap(_corners[(unsigned)Corner::URB], _corners[(unsigned)Corner::DLB]);

    std::swap(_edges[(unsigned)Edge::UB], _edges[(unsigned)Edge::DB]);
    std::swap(_edges[(unsigned)Edge::BL], _edges[(unsigned)Edge::BR]);

    return *this;
}

Cube& Cube::RotationD() {
    Cubie tmp                       = _corners[(unsigned)Corner::DLB];
    _corners[(unsigned)Corner::DLB] = _corners[(unsigned)Corner::DRB];
    _corners[(unsigned)Corner::DRB] = _corners[(unsigned)Corner::DRF];
    _corners[(unsigned)Corner::DRF] = _corners[(unsigned)Corner::DLF];
    _corners[(unsigned)Corner::DLF] = tmp;

    tmp                             = _edges[(unsigned)Edge::DB];
    _edges[(unsigned)Edge::DB]      = _edges[(unsigned)Edge::DR];
    _edges[(unsigned)Edge::DR]      = _edges[(unsigned)Edge::DF];
    _edges[(unsigned)Edge::DF]      = _edges[(unsigned)Edge::DL];
    _edges[(unsigned)Edge::DL]      = tmp;

    return *this;
}

Cube& Cube::OppositeRotationD() {
    Cubie tmp                       = _corners[(unsigned)Corner::DLF];
    _corners[(unsigned)Corner::DLF] = _corners[(unsigned)Corner::DRF];
    _corners[(unsigned)Corner::DRF] = _corners[(unsigned)Corner::DRB];
    _corners[(unsigned)Corner::DRB] = _corners[(unsigned)Corner::DLB];
    _corners[(unsigned)Corner::DLB] = tmp;

    tmp                             = _edges[(unsigned)Edge::DL];
    _edges[(unsigned)Edge::DL]      = _edges[(unsigned)Edge::DF];
    _edges[(unsigned)Edge::DF]      = _edges[(unsigned)Edge::DR];
    _edges[(unsigned)Edge::DR]      = _edges[(unsigned)Edge::DB];
    _edges[(unsigned)Edge::DB]      = tmp;

    return *this;
}

Cube& Cube::RotationD2() {
    std::swap(_corners[(unsigned)Corner::DLB], _corners[(unsigned)Corner::DRF]);
    std::swap(_corners[(unsigned)Corner::DRB], _corners[(unsigned)Corner::DLF]);

    std::swap(_edges[(unsigned)Edge::DB], _edges[(unsigned)Edge::DF]);
    std::swap(_edges[(unsigned)Edge::DR], _edges[(unsigned)Edge::DL]);

    return *this;
}

Cube &Cube::Rotate(Cube::Rotation rotation) {
    switch (rotation) {
        case Cube::Rotation::L: return RotationL();
        case Cube::Rotation::OppositeL: return OppositeRotationL();
        case Cube::Rotation::L2: return RotationL2();

        case Cube::Rotation::R: return RotationR();
        case Cube::Rotation::OppositeR: return OppositeRotationR();
        case Cube::Rotation::R2: return RotationR2();

        case Cube::Rotation::U: return RotationU();
        case Cube::Rotation::OppositeU: return OppositeRotationU();
        case Cube::Rotation::U2: return RotationU2();

        case Cube::Rotation::D: return RotationD();
        case Cube::Rotation::OppositeD: return OppositeRotationD();
        case Cube::Rotation::D2: return RotationD2();

        case Cube::Rotation::F: return RotationF();
        case Cube::Rotation::OppositeF: return OppositeRotationF();
        case Cube::Rotation::F2: return RotationF2();

        case Cube::Rotation::B: return RotationB();
        case Cube::Rotation::OppositeB: return OppositeRotationB();
        case Cube::Rotation::B2: return RotationB2();

        case Cube::Rotation::End: throw std::logic_error("End rotation was passed into Rotate function");
    }
}

Cube Cube::Rotate(const Cube &cube, Cube::Rotation rotation) {
    Cube copy(cube);
    return copy.Rotate(rotation);
}
