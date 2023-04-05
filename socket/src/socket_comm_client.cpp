#include "socket_comm_client.hpp"

socket_comm_client::socket_comm_client(const std::string &host, int port) :
    socket_comm(host, port, true),
    socket_(this->ioContext_) {
}

void socket_comm_client::run() {
//    this->socket_.async_receive()
}

socket_comm_client::~socket_comm_client() {

}