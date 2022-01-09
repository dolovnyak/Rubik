#pragma once

#include "DynamicBuffer.hpp"
#include "Cube.hpp"

class HeuristicDB {
 public:
    HeuristicDB() = delete;
    explicit HeuristicDB(size_t size);

    void SetMoveNumbersByIndex(size_t index, uint8_t move_numbers);
    [[nodiscard]] uint8_t GetMoveNumbersByIndex(uint32_t index) const;
    [[nodiscard]] uint8_t GetMoveNumbersByCubeState(const Cube& cube) const;

 private:
    DynamicBuffer _buffer;

    virtual int GenerateDbIndexByCubeState(const Cube& cube) const = 0;
};
