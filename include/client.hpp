#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

int connectToServer(const std::string& host);
void sendStreamAllRequest(int sockfd);
void sendResendRequest(int sockfd, uint8_t seq);

#endif