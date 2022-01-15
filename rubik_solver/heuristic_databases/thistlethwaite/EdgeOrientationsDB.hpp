#pragma once

#include "HeuristicDB.hpp"

/// This db contains orientations for edges, it's first step in thistlethwaite algorithm
class EdgeOrientationsDB : public HeuristicDB {
 public:
    EdgeOrientationsDB();

    [[nodiscard]] size_t GenerateDbIndexByCube(const Cube& cube) const override;
};
