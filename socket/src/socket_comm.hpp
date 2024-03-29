#pragma once

#include <string>
#include "spdlog/spdlog.h"
#include <boost/asio.hpp>

class socket_comm {
protected:
    boost::asio::io_context ioContext_;
    std::unique_ptr<spdlog::logger> logger_;
    const std::string host_;
    int port_;

    socket_comm(const std::string& host, int port, bool isClient);
public:
    socket_comm() = delete;
    socket_comm(socket_comm&) = delete;
    socket_comm(const socket_comm&) = delete;
    socket_comm(socket_comm&&) = delete;

    virtual void run() = 0;
    virtual ~socket_comm() = default;
};