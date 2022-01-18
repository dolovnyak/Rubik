#pragma once

#include "Cube.hpp"

/// There are 12 edges, two orientations for each, and the orientations of 11 dictate the orientation of the 12th
/// There are then 2^11 orientations, and the database needs 2^11 / 1024^2 / 2 = 1KB on disk.
static constexpr size_t kThistlethwaiteStep1DbSize = 2048;

/// Step 1 db in thistlethwaite algorithm.
class EdgeOrientationsDB {
 public:
    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const;
};
