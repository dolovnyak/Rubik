#include "HeuristicDB.hpp"

HeuristicDB::HeuristicDB(size_t size)
: _buffer(size, 0xFF)
{}

void HeuristicDB::SetMoveNumbersByIndex(size_t index, uint8_t move_numbers) {
    _buffer.Set(index, move_numbers);
}

uint8_t HeuristicDB::GetMoveNumbersByIndex(uint32_t index) const {
    return _buffer.Get(index);
}

uint8_t HeuristicDB::GetMoveNumbersByCubeState(const Cube& cube) const {
    return GetMoveNumbersByIndex(GenerateDbIndexByCubeState(cube));
}
