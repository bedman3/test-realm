#pragma once

#include "socket_comm.hpp"

class socket_comm_server : public socket_comm {
    boost::asio::ip::tcp::acceptor acceptor_;

    void async_accept_handle(const boost::system::error_code& errorCode) {
    }
public:
    socket_comm_server(const std::string& host, int port);
    void run() override;
    ~socket_comm_server() override;
};