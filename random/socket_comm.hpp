#pragma once

#include <string>

class socket_comm {

    const std::string host;
    int port;
    bool isClient;

    public:
    socket_comm() = delete;
    socket_comm(const std::string& host, int port, bool isClient);
    socket_comm(socket_comm&) = delete;
    socket_comm(const socket_comm&) = delete;
    socket_comm(socket_comm&&) = delete;

    void run() {
        if (isClient) {
            
        } else {}
        
    }
};