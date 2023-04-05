#include "socket_comm_server.hpp"
#include "socket_comm_client.hpp"
#include <memory>
#include <iostream>

const std::string& HOST = "127.0.0.1";
const int STARTING_PORT = 8001;
const int NUM_OF_CLIENTS = 5;
const int PORT_OFFSET = 100;
const int NUM_OF_THREADS_CAPACITY = NUM_OF_CLIENTS + 3;

int main() {
    boost::asio::thread_pool io(NUM_OF_THREADS_CAPACITY);
    std::cout << "Start of program" << std::endl;

    boost::asio::post(io, [] {
        auto server = std::make_shared<socket_comm_server>(HOST, STARTING_PORT);
        server->run();
    });

    for (int i = 0; i < NUM_OF_CLIENTS; ++i) {
        boost::asio::post(io, [i] {
            auto client = std::make_shared<socket_comm_client>(HOST, STARTING_PORT + i + PORT_OFFSET);
            client->run();
        });
    }
    io.join();
    std::cout << "End of program" << std::endl;
}