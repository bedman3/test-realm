#include "socket_comm.hpp"
#include <iostream>

socket_comm::socket_comm(const std::string& host, int port, bool isClient) : host_(host), port_(port) {
    std::cout << "Created socket [" << (isClient ? "client" : "server") << "] with host_ ip [" << host << "] and port_ [" << port << "]" << std::endl;
}