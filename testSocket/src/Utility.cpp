//
// Created by martin on 5/24/21.
//

#include "Utility.hpp"

std::string Utility::to_string(const boost::asio::ip::tcp::endpoint& endpoint) {
    std::stringstream ss;
    ss << endpoint;
    return ss.str();
}

