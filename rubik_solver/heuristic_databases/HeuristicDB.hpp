#pragma once

#include "DynamicBits4Buffer.hpp"
#include "Cube.hpp"
#include <fstream>
#include <queue>
#include "logs.hpp"

template <size_t Size, class DB>
class HeuristicDB {
 public:
    HeuristicDB() : _buffer(Size, 0xFF) {}

    inline void SetMovesNumberByState(const Cube& cube, uint8_t move_numbers) {
        SetMovesNumberByIndex(_db.GenerateDbIndexByCube(cube), move_numbers);
        ++_filled_number;
    }

    [[nodiscard]] inline bool IsStateVisited(const Cube& cube, uint8_t move_numbers) const {
        return move_numbers < GetMovesNumberByIndex(_db.GenerateDbIndexByCube(cube));
    }

    inline void SetMovesNumberByIndex(size_t index, uint8_t move_numbers) {
        _buffer.Set(index, move_numbers);
    }

    [[nodiscard]] inline uint8_t GetEstimatedMovesNumber(const Cube& cube) const {
        return GetMovesNumberByIndex(_db.GenerateDbIndexByCube(cube));
    }

    [[nodiscard]] inline bool IsFull() const {
        return _filled_number == _buffer.GetSize();
    }

    [[nodiscard]] inline size_t GetFilledNumber() {
        return _filled_number;
    }

    inline void WriteDbToFile(std::string_view file_path) const {
        std::ofstream stream(file_path, std::ios::out | std::ios::binary | std::ios::trunc);

        if (!stream.is_open())
            throw std::logic_error("Failed to open file for writing.");

        stream.write(reinterpret_cast<const char*>(_buffer.GetConstRawData()),
                     static_cast<std::streamsize>(_buffer.GetStorageSize()));

        stream.close();
    }

    inline bool ParseDbFromFile(std::string_view file_path) {
        std::ifstream reader(file_path, std::ios::in | std::ios::ate);

        if (!reader.is_open()) {
            LOG_INFO("file with name \"", file_path, "\" didn't open");
            return false;
        }

        std::streamsize file_size = reader.tellg();
        if (file_size != static_cast<std::streamsize>(_buffer.GetStorageSize())) {
            reader.close();
            throw std::runtime_error("Database file size doesn't match with database storage size.\n"
                                     "FILE_SIZE is \"" + std::to_string(file_size) + "\" STORAGE_SIZE is \"" +
                                     std::to_string(_buffer.GetStorageSize()) + "\"");
        }

        reader.seekg(0, std::ios::beg);
        reader.read(reinterpret_cast<char*>(_buffer.GetRawData()),file_size);
        reader.close();
        _filled_number = _buffer.GetSize();

        return true;
    }

 private:
    DynamicBits4Buffer _buffer;
    DB _db;
    size_t _filled_number = 0;

    [[nodiscard]] inline uint8_t GetMovesNumberByIndex(size_t index) const {
        return _buffer.Get(index);
    }
};
