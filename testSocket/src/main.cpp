//
// Created by martin on 5/22/21.
//

#include <iostream>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "CommandParser.h"
#include "Server.h"


//void handleRead(boost::array<char, HEADER_BUFFER_SIZE> buf, const boost::system::error_code& error) {
//    if (error) {
//        std::cerr << "Detected error at reading, exiting" << std::endl;
//        std::cerr << error.message() << std::endl;
//    } else {
//        std::cout << "Read: [" << buf.data() << "]" << std::endl;
//    }
//}
//
//void handleAccept(boost::asio::ip::tcp::socket &socket, const boost::system::error_code& error) {
//    if (error) {
//        std::cerr << "Detected error at accepting, exiting" << std::endl;
//        std::cerr << error.message() << std::endl;
//    } else {
//        boost::array<char, HEADER_BUFFER_SIZE> buf;
//        boost::asio::async_read(socket, boost::asio::buffer(buf), boost::bind(&handleRead, buf, boost::asio::placeholders::error));
//    }
//
//    std::cout << "Accepted Connection" << std::endl;
//}

int main(int argc, char *argv[]) {
    std::shared_ptr<Endpoint> serverEndpoint;
    std::vector<std::shared_ptr<Endpoint>> clientEndpoints;
    std::shared_ptr<boost::asio::io_context> ioContext = std::make_shared<boost::asio::io_context>();

    if (!CommandParser::parse(argc, argv, serverEndpoint, clientEndpoints)) {
        std::cerr << "Parsing error, exiting" << std::endl;
        return 0;
    }

    try {
        std::cout << "Initializing server" << std::endl;

        Server server(serverEndpoint, ioContext);

//        server.async_run();


//        std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> clientSocketsList;
//        std::cout << "Building client socket" << std::endl;
//        boost::asio::ip::tcp::socket clientSocket(ioContext_);

        ioContext->run();
    } catch (std::exception& e) {
        std::cerr << "Main thread exception \n" << e.what() << std::endl;
    }

    return 0;
}