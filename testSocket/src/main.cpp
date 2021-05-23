//
// Created by martin on 5/22/21.
//

#include <iostream>
#include <cstring>
#include "yaml-cpp/yaml.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class Endpoint {
    std::string host_;
    short port_;
public:
    Endpoint(std::string host, short port) : host_(host), port_(port) {}

    const std::string &getHost() { return host_; }
    short getPort() { return port_; }
};

class asio;

bool hasNextArgument(int argc, int i) {
    return (argc - i > 1);
}

bool isStringSame(const char *str1, const char *str2) {
    return (std::strcmp(str1, str2) == 0);
}

void printFunc() {
    std::cout << "Accepted Connection" << std::endl;
}

int main(int argc, char *argv[]) {
    std::string configPath;
    std::shared_ptr<Endpoint> serverEndpoint;
    std::vector<std::shared_ptr<Endpoint>> clientEndpoints;
    bool notExit = true;

    if (argc < 2) {
        std::cout << "no arguments, exiting" << std::endl;
        return 0;
    }

    for (int i = 0; i < argc; ++i) {
        if (isStringSame(argv[i], "--configPath") && hasNextArgument(argc, i)) {
            configPath = std::string(argv[++i]);
        }
    }

    std::cout << "configPath is [" << configPath << "]" << std::endl;
    YAML::Node config = YAML::LoadFile(configPath);

    std::cout << "YAML String: \n" << Dump(config) << std::endl;

    serverEndpoint = std::make_shared<Endpoint>(
            config["config"]["serverHost"].as<std::string>(),
            config["config"]["serverPort"].as<short>());

    std::cout << "serverHost is [" << serverEndpoint->getHost() << "] and serverPort is ["
              << serverEndpoint->getPort() << "]" << std::endl;

    uint numClients = config["config"]["clientConnections"].size();
    for (int i = 0; i < numClients; ++i) {
        std::shared_ptr<Endpoint> sharedPtr = std::make_shared<Endpoint>(
                config["config"]["clientConnections"][i]["host"].as<std::string>(),
                config["config"]["clientConnections"][i]["port"].as<short>());
        clientEndpoints.push_back(sharedPtr);
        std::cout << "clientConnections " << i + 1 << " host [" << sharedPtr->getHost() << "] and port ["
                  << sharedPtr->getPort() << "]" << std::endl;

    }

    std::cout << "finished loading config" << std::endl;

    try {
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::acceptor acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), serverEndpoint->getPort()));
        boost::system::error_code ignore_error;
        boost::asio::streambuf buffer;
        size_t buf_size = 20, headerBufferSize = 4;
        std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> clientSocketsList;

        std::cout << "Building server socket" << std::endl;
        boost::asio::ip::tcp::socket serverSocket(ioService);

        std::cout << "Building client socket" << std::endl;
        boost::asio::ip::tcp::socket clientSocket(ioService);

        std::cout << "Accept to socket" << std::endl;
        acceptor.async_accept(serverSocket, boost::bind(&printFunc));
        ioService.run();

        while (notExit) {
            size_t bytesTransferred = boost::asio::read(serverSocket, buffer, boost::asio::transfer_exactly(buf_size));
            boost::asio::streambuf::const_buffers_type bufs = buffer.data();
            std::cout << "Read [" << std::string(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + buf_size) << "]" << std::endl;
        }

//        while (true) {
//            boost::asio::read(socket, buffer, ignore_error);
//        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}