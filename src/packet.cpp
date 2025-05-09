#include "packet.hpp"
#include "utils.hpp"

Packet parsePacket(const uint8_t* data) {
    Packet packet;
    packet.symbol = std::string(reinterpret_cast<const char*>(data), 4);
    packet.indicator = data[4];
    packet.quantity = readInt32BigEndian(&data[5]);
    packet.price = readInt32BigEndian(&data[9]);
    packet.sequence = readInt32BigEndian(&data[13]);
    return packet;
}