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

class Server {
    std::shared_ptr<Endpoint> serverEndpoint_;
    std::shared_ptr<boost::asio::io_context> ioContext_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    char buf_[2048];
    ChatMessage chatMsg_;

    void doReadHeader();

public:
    Server(std::shared_ptr<Endpoint>& serverEndpoint, std::shared_ptr<boost::asio::io_context>& ioContext);
    ~Server();

    void async_run();

    void doReadBody();
    void doReadChatMessage();
};


#endif //TESTSOCKET_SERVER_H
