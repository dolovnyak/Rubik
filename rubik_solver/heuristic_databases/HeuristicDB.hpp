#pragma once

#include "DynamicBits4Buffer.hpp"
#include "Cube.hpp"
#include <fstream>

class HeuristicDB {
 public:
    HeuristicDB() = delete;
    explicit HeuristicDB(size_t size);

    void SetMovesNumberByState(const Cube& cube, uint8_t move_numbers);
    [[nodiscard]] bool IsMovesNumbersBetter(const Cube& cube, uint8_t move_numbers) const;
    void SetMovesNumberByIndex(size_t index, uint8_t move_numbers);
    [[nodiscard]] uint8_t GetEstimatedMovesNumber(const Cube& cube) const;
    [[nodiscard]] bool IsFull() const;
    void WriteDbToFile(const std::string& file_path) const;
    bool ParseDbFromFile(const std::string& file_path);
    [[nodiscard]] size_t GetFilledNumber();

 private:
    DynamicBits4Buffer _buffer;
    size_t _filled_number = 0;

    [[nodiscard]] uint8_t GetMovesNumberByIndex(size_t index) const;
    [[nodiscard]] virtual size_t GenerateDbIndexByCube(const Cube& cube) const = 0;
};
