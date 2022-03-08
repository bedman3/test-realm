
#include "Session.hpp"

Session::Session(boost::asio::ip::tcp::socket&& socket) : socket_(std::move(socket))) {
}

Session::~Session() {
}

auto Session::getSocketRemoteEndpoint() const -> boost::asio::ip::tcp::endpoint {
    return socket_.remote_endpoint();
}