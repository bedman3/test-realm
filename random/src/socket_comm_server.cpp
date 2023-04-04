#include "socket_comm_server.hpp"

socket_comm_server::socket_comm_server(const std::string &host, int port) :
        socket_comm(host, port, false),
        acceptor_(this->ioContext_,
                  boost::asio::ip::tcp::endpoint(
                         boost::asio::ip::address_v4::from_string(host), port)) {}

void socket_comm_server::run() {
    this->acceptor_.async_accept([this] (std::error_code ec, boost::asio::ip::tcp::socket&& newSocket) {
        if (!ec) {
            logger_->info("Accept connection from " + newSocket.remote_endpoint().address().to_string() + ":" + std::to_string(newSocket.remote_endpoint().port()));
//            newSocket.async_read_some(socket_comm_server::async_read_handle);
        } else {
            logger_->error(ec.message());
        }
    });
    this->ioContext_.run();
}

socket_comm_server::~socket_comm_server() {

}