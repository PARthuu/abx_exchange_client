#include "client.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

constexpr int PORT = 3000;

int connectToServer(const std::string& host) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server = gethostbyname(host.c_str());
    if (!server) return -1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;

    std::memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        return -1;

    return sockfd;
}

void sendStreamAllRequest(int sockfd) {
    uint8_t request[2] = {1, 0};
    send(sockfd, request, 2, 0);
}

void sendResendRequest(int sockfd, uint8_t seq) {
    uint8_t request[2] = {2, seq};
    send(sockfd, request, 2, 0);
}