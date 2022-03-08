#include "Server.hpp"

#ifndef TESTSOCKET_SESSION_H
#define TESTSOCKET_SESSION_H

class Session {
    boost::asio::ip::tcp::socket socket_;
public:
    Session(boost::asio::ip::tcp::socket&& socket);

    auto getSocketRemoteEndpoint() const -> boost::asio::ip::tcp::endpoint;
    void doReadHeader();
};

#endif //TESTSOCKET_SESSION_H