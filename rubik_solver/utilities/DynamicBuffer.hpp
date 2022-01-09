#pragma once

#include <cstdint>
#include <cstring>

class DynamicBuffer {
 public:
    DynamicBuffer(size_t size, uint8_t value)
    : _size(size), _data(size == 0 ? nullptr : new uint8_t[size / 2 + 1]) {
        for (size_t i = 0; i < size; ++i) {
            _data[i] = value;
        }
    }

    ~DynamicBuffer() {
        delete[] _data;
        _data = nullptr;
    }

    inline uint8_t Get(size_t index) const;
    inline void Set(size_t index, uint8_t value);

 private:
    size_t      _size;
    uint8_t*    _data;
};


inline uint8_t DynamicBuffer::Get(size_t index) const {
    size_t i = index / 2;
    uint8_t value = _data[i];

    // If odd return last 4 bits, if even return first 4 bits.
    return index % 2 ? value & 0x0F : value >> 4;
}

inline void DynamicBuffer::Set(size_t index, uint8_t value) {
    size_t i = index / 2;
    uint8_t current_value = _data[i];

    if (index % 2) {
        // Odd: last 4 bits.
        _data[i] = (current_value & 0xF0) | (value & 0x0F);
    }
    else {
        // Even: first 4 bits.
        _data[i] = (value << 4) | (current_value & 0x0F);
    }
}
