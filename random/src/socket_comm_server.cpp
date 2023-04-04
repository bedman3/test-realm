#include "socket_comm_server.hpp"

socket_comm_server::socket_comm_server(const std::string &host, int port) :
        socket_comm(host, port, false),
        acceptor_(this->ioContext_,
                  boost::asio::ip::tcp::endpoint(
                         boost::asio::ip::address_v4::from_string(host), port)) {}

void socket_comm_server::run() {
    this->acceptor_.async_accept([this] (std::error_code ec, boost::asio::ip::tcp::socket&& newSocket) {

    });
}

socket_comm_server::~socket_comm_server() {

}