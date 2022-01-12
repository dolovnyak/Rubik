#include "HeuristicDB.hpp"
#include "logs.hpp"

HeuristicDB::HeuristicDB(size_t size)
: _buffer(size, 0xFF)
{}

void HeuristicDB::SetMovesNumberByIndex(size_t index, uint8_t move_numbers) {
    _buffer.Set(index, move_numbers);
}

uint8_t HeuristicDB::GetMovesNumberByIndex(size_t index) const {
    return _buffer.Get(index);
}

uint8_t HeuristicDB::GetEstimatedMovesNumber(const Cube& cube) const {
    return GetMovesNumberByIndex(GenerateDbIndexByCube(cube));
}

void HeuristicDB::SetMovesNumberByState(const Cube &cube, uint8_t move_numbers) {
    SetMovesNumberByIndex(GenerateDbIndexByCube(cube), move_numbers);
    ++_filled_number;
}

bool HeuristicDB::IsStateVisited(const Cube& cube, uint8_t move_numbers) const {
    return move_numbers < GetMovesNumberByIndex(GenerateDbIndexByCube(cube));
}

bool HeuristicDB::IsFull() const {
    return _filled_number == _buffer.GetSize();
}

void HeuristicDB::WriteDbToFile(std::string_view file_path) const {
    std::ofstream stream(file_path, std::ios::out | std::ios::binary | std::ios::trunc);

    if (!stream.is_open())
        throw std::logic_error("Failed to open file for writing.");

    stream.write(reinterpret_cast<const char*>(_buffer.GetConstRawData()),
                 static_cast<std::streamsize>(_buffer.GetStorageSize()));

    stream.close();
}

bool HeuristicDB::ParseDbFromFile(std::string_view file_path) {
    std::ifstream reader(file_path, std::ios::in | std::ios::ate);

    if (!reader.is_open()) {
        LOG_INFO("file with name \"", file_path, "\" didn't open");
        return false;
    }

    std::streamsize file_size = reader.tellg();
    if (file_size != static_cast<std::streamsize>(_buffer.GetStorageSize())) {
        reader.close();
        throw std::runtime_error("Database file size doesn't match with database storage size");
    }

    reader.seekg(0, std::ios::beg);
    reader.read(reinterpret_cast<char*>(_buffer.GetRawData()),file_size);
    reader.close();
    _filled_number = _buffer.GetSize();

    return true;
}

size_t HeuristicDB::GetFilledNumber() {
    return _filled_number;
}
