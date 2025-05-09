#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>
#include <cstdint>

struct Packet {
    std::string symbol;
    char indicator;
    int32_t quantity;
    int32_t price;
    int32_t sequence;
};

Packet parsePacket(const uint8_t* data);

#endif