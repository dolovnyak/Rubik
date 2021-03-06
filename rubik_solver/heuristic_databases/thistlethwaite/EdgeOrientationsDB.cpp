#include "EdgeOrientationsDB.hpp"

size_t EdgeOrientationsDB::GenerateDbIndexByCube(const Cube& cube) const {
    /// Treat the orientations as a base-2 number, and convert it to base-10.
    /// Because 11 edges dictate the orientation of the 12th, only 11 edges matter in this calculation.
    return cube.GetEdgeOrientation(Cube::Edge::UB) * 1024 +
           cube.GetEdgeOrientation(Cube::Edge::UR) * 512 +
           cube.GetEdgeOrientation(Cube::Edge::UF) * 256 +
           cube.GetEdgeOrientation(Cube::Edge::UL) * 128 +
           cube.GetEdgeOrientation(Cube::Edge::FR) * 64 +
           cube.GetEdgeOrientation(Cube::Edge::FL) * 32 +
           cube.GetEdgeOrientation(Cube::Edge::BL) * 16 +
           cube.GetEdgeOrientation(Cube::Edge::BR) * 8 +
           cube.GetEdgeOrientation(Cube::Edge::DF) * 4 +
           cube.GetEdgeOrientation(Cube::Edge::DL) * 2 +
           cube.GetEdgeOrientation(Cube::Edge::DB);
}
