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
#include "Utility.h"
#include "Session.h"
#include "unordered_set"

class Server {
    std::shared_ptr<Endpoint> serverEndpoint_;
    std::shared_ptr<boost::asio::io_context> ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> socketVector_;
    std::shared_ptr<spdlog::async_logger> logger_;
    std::unordered_set<Session> sessions_;
    char buf_[2048];


    ChatMessage chatMsg_;

    void doReadHeader(std::shared_ptr<boost::asio::ip::tcp::socket> socketPtr);

public:
    Server(std::shared_ptr<Endpoint>& serverEndpoint, std::shared_ptr<boost::asio::io_context>& ioContext,
           std::shared_ptr<spdlog::async_logger> logger);
    ~Server();

    void async_run();

    void doReadBody();
    void doReadChatMessage(const ChatMessage *chatMessage, const std::shared_ptr<boost::asio::ip::tcp::socket>& socketPtr);
};


#endif //TESTSOCKET_SERVER_H
