#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <unistd.h>
#include <sys/socket.h>
#include "client.hpp"
#include "packet.hpp"

constexpr int PACKET_SIZE = 17;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <hostname>\n";
        return 1;
    }

    int sockfd = connectToServer(argv[1]);
    if (sockfd < 0) {
        std::cerr << "Failed to connect to server\n";
        return 1;
    }

    sendStreamAllRequest(sockfd);

    std::vector<Packet> packets;
    std::set<int> received;
    uint8_t buffer[PACKET_SIZE];

    while (recv(sockfd, buffer, PACKET_SIZE, 0) == PACKET_SIZE) {
        Packet p = parsePacket(buffer);
        packets.push_back(p);
        received.insert(p.sequence);
    }

    close(sockfd);

    int maxSeq = *received.rbegin();
    for (int i = 1; i < maxSeq; ++i) {
        if (received.find(i) == received.end()) {
            int rsock = connectToServer(argv[1]);
            if (rsock < 0) continue;
            sendResendRequest(rsock, static_cast<uint8_t>(i));
            if (recv(rsock, buffer, PACKET_SIZE, 0) == PACKET_SIZE) {
                Packet p = parsePacket(buffer);
                packets.push_back(p);
            }
            close(rsock);
        }
    }

    std::sort(packets.begin(), packets.end(), [](const Packet& a, const Packet& b) {
        return a.sequence < b.sequence;
    });

    std::ofstream o("packets.json");
    o << "[\n";
    
    bool first = true;
    for (const auto& p : packets) {
        if (!first) {
            o << ",\n";
        }
        first = false;
        
        o << "    {\n";
        o << "        \"symbol\": \"" << p.symbol << "\",\n";
        o << "        \"type\": \"" << p.indicator << "\",\n";
        o << "        \"qty\": " << p.quantity << ",\n";
        o << "        \"price\": " << std::fixed << std::setprecision(2) << p.price << ",\n";
        o << "        \"seq\": " << p.sequence << "\n";
        o << "    }";
    }
    
    o << "\n]";
    o.close();
    
    return 0;
}