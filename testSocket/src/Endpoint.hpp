//
// Created by martin on 5/23/21.
//

#ifndef TESTSOCKET_ENDPOINT_H
#define TESTSOCKET_ENDPOINT_H


class Endpoint {
    std::string host_;
    short port_;
public:
    Endpoint(std::string host, short port) : host_(host), port_(port) {}

    const std::string &getHost() { return host_; }
    short getPort() { return port_; }
};


#endif //TESTSOCKET_ENDPOINT_H
