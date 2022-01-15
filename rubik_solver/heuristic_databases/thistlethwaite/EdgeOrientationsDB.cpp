#include "EdgeOrientationsDB.hpp"

/// There are 12 edges, two orientations for each, and the orientations of 11 dictate the orientation of the 12th
/// There are then 2^11 orientations, and the database needs 2^11 / 1024^2 / 2 = 1KB on disk.
EdgeOrientationsDB::EdgeOrientationsDB() : HeuristicDB(2048) {}

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
