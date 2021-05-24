//
// Created by martin on 5/24/21.
//

#ifndef SOCKETAPP_UTILITY_H
#define SOCKETAPP_UTILITY_H

#include <iostream>
#include <cstring>
#include <boost/asio.hpp>

class Utility {
public:
    static std::string to_string(const boost::asio::ip::tcp::endpoint& endpoint);

};


#endif //SOCKETAPP_UTILITY_H
