//
// Created by martin on 5/23/21.
//

#include <iostream>
#include "Server.h"

Server::Server(std::shared_ptr <Endpoint>& serverEndpoint, std::shared_ptr<boost::asio::io_context>& ioContext) :
        serverEndpoint_(serverEndpoint),
        ioContext_(ioContext),
        acceptor_(*ioContext_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), serverEndpoint_->getPort())),
        socket_(*ioContext_)
        {
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    async_run();
}

void Server::async_run() {
    std::cout << "Server accept to socket at endpoint [" << acceptor_.local_endpoint() << "]" << std::endl;
    acceptor_.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            socket_ = std::move(socket);
            if (!ec) {
                doReadHeader();
            } else {
                std::cerr << "Error occurred while accepting socket: " << ec.message() << std::endl;
            }

            async_run();
        }
    );
}

void Server::doReadHeader() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(buf_, headerBufferSize),
//                            boost::asio::transfer_exactly(headerBufferSize),
                            [this](boost::system::error_code ec, std::size_t bytesTransferred) {
        std::cout << "Socket read header bytes [" << bytesTransferred << "]" << std::endl;
        if (!ec) {
            const MessageHeader* messageHeader = static_cast<const MessageHeader*>((void *)this->buf_);
            std::cout << "Received message with message type [" << messageHeader->messageType_ << "] and message length [" << messageHeader->length_ << "]" << std::endl;

            switch (messageHeader->messageType_) {
                case CHAT_MESSAGE:
                    doReadChatMessage();
                    break;
                default:
                    std::cout << "Unknown message type [" << messageHeader->messageType_ << "], dropping messages" << std::endl;
            }
            doReadBody();
        } else {
            std::cerr << "Error occurred while reading header: " << ec.message() << std::endl;
        }
    });
}

void Server::doReadChatMessage() {

}

void Server::doReadBody() {

}

Server::~Server() {
    std::cout << "Server destructor called" << std::endl;
    if (socket_.is_open()) {
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket_.close();
    }
}
