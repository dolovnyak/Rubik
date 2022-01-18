#pragma once

#include <cstdint>
#include <cstring>
#include <algorithm>

class DynamicBits4Buffer {
 public:
    DynamicBits4Buffer(size_t size, uint8_t value)
    : _size(size), _storage_size(size / 2 + 1), _data(size == 0 ? nullptr : new uint8_t[_storage_size]) {
        for (size_t i = 0; i < size / 2 + 1; ++i) {
            _data[i] = value;
        }
    }

    DynamicBits4Buffer(DynamicBits4Buffer&& buffer) {
        std::swap(_data, buffer._data);
        std::swap(_storage_size, buffer._storage_size);
        std::swap(_size, buffer._size);
    }

    ~DynamicBits4Buffer() {
        delete[] _data;
        _data = nullptr;
    }

    [[nodiscard]] inline uint8_t Get(size_t index) const;
    inline void Set(size_t index, uint8_t value);
    [[nodiscard]] inline size_t GetSize() const;
    [[nodiscard]] inline size_t GetStorageSize() const;
    [[nodiscard]] inline const uint8_t* GetConstRawData() const;
    [[nodiscard]] inline uint8_t* GetRawData();

 private:
    size_t      _size = 0;
    size_t      _storage_size = 0;
    uint8_t*    _data = nullptr;
};


inline uint8_t DynamicBits4Buffer::Get(size_t index) const {
    size_t i = index / 2;
    uint8_t value = _data[i];

    /// If odd return last 4 bits, if even return first 4 bits.
    return index % 2 ? value & 0x0F : value >> 4;
}

inline void DynamicBits4Buffer::Set(size_t index, uint8_t value) {
    size_t i = index / 2;
    uint8_t current_value = _data[i];

    if (index % 2) {
        /// Odd: last 4 bits.
        _data[i] = (current_value & 0xF0) | (value & 0x0F);
    }
    else {
        /// Even: first 4 bits.
        _data[i] = (value << 4) | (current_value & 0x0F);
    }
}

inline size_t DynamicBits4Buffer::GetSize() const {
    return _size;
}

inline size_t DynamicBits4Buffer::GetStorageSize() const {
    return _storage_size;
}

const uint8_t* DynamicBits4Buffer::GetConstRawData() const {
    return _data;
}

uint8_t* DynamicBits4Buffer::GetRawData() {
    return _data;
}

