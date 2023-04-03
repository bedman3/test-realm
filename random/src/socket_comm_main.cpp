
#include "socket_comm.hpp"
#include <memory>
#include <iostream>

int main() {
    const std::string& HOST = "127.0.0.1";
    int startingPort = 8001;
    int numOfClients = 5;
    int portOffset = 100;
    std::cout << "Start of program" << std::endl;

    auto server = std::make_shared<socket_comm>(HOST, startingPort, false);
    server->run();
    for (int i = 0; i < numOfClients; ++i) {
        auto client = std::make_shared<socket_comm>(HOST, startingPort + i + portOffset, true);
        client->run();
    }
    std::cout << "End of program" << std::endl;
}