#include "socket_comm_client.hpp"

socket_comm_client::socket_comm_client(const std::string &host, int port) : socket_comm(host, port, true) {}

void socket_comm_client::run() {

}

socket_comm_client::~socket_comm_client() {

}