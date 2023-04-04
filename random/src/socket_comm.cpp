#include "socket_comm.hpp"
#include <iostream>

socket_comm::socket_comm(const std::string& host, int port, bool isClient) : host(host), port(port), isClient(isClient) {
    std::cout << "Created socket [" << (isClient ? "client" : "server") << "] with host ip [" << host << "] and port [" << port << "]" << std::endl;
}

void socket_comm::run() {
    if (isClient) {

    } else {

    }
}