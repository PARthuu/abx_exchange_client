#include "utils.hpp"

int32_t readInt32BigEndian(const uint8_t* buffer) {
    return (buffer[0] << 24) |
           (buffer[1] << 16) |
           (buffer[2] << 8)  |
           buffer[3];
}