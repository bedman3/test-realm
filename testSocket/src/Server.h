//
// Created by martin on 5/23/21.
//

#ifndef TESTSOCKET_SERVER_H
#define TESTSOCKET_SERVER_H

#include <memory>
#include "Endpoint.h"
#include "Message.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <spdlog/async_logger.h>

class Server {
    std::shared_ptr<Endpoint> serverEndpoint_;
    std::shared_ptr<boost::asio::io_context> ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    std::shared_ptr<spdlog::async_logger> logger_;
    char buf_[2048];
    ChatMessage chatMsg_;

    void doReadHeader();

public:
    Server(std::shared_ptr<Endpoint>& serverEndpoint, std::shared_ptr<boost::asio::io_context>& ioContext,
           std::shared_ptr<spdlog::async_logger> logger);
    ~Server();

    void async_run();

    void doReadBody();
    void doReadChatMessage(const ChatMessage *chatMessage);
};


#endif //TESTSOCKET_SERVER_H
