cmake_minimum_required(VERSION 3.10)
project(abx_client)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(abx_client
    src/main.cpp
    src/client.cpp
    src/packet.cpp
    src/utils.cpp
)