//
// Created by martin on 5/23/21.
//

#include <iostream>
#include "Server.h"

Server::Server(std::shared_ptr <Endpoint>& serverEndpoint, std::shared_ptr<boost::asio::io_context>& ioContext,
               std::shared_ptr<spdlog::async_logger> logger) :
        serverEndpoint_(serverEndpoint),
        ioContext_(ioContext),
        acceptor_(*ioContext_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), serverEndpoint_->getPort())),
        socket_(*ioContext_),
        logger_(logger)
        {
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    async_run();
}

void Server::async_run() {
    logger_->info("Server accept to socket at endpoint [" + acceptor_.local_endpoint().address().to_string() + "]");
    acceptor_.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            socket_ = std::move(socket);
            if (!ec) {
                doReadHeader();
            } else {
                logger_->error("Error occurred while accepting socket: " + ec.message());
            }

            async_run();
        }
    );
}

void Server::doReadHeader() {
    boost::asio::async_read(socket_,
                            boost::asio::buffer(buf_, HEADER_BUFFER_SIZE),
                            [this](boost::system::error_code ec, std::size_t bytesTransferred) {
        logger_->debug("Socket read header bytes [" + std::to_string(bytesTransferred) + "]");
        if (!ec) {
            const MessageHeader* messageHeader = static_cast<const MessageHeader*>((void *)this->buf_);
            logger_->debug("Received message with message type [" + std::to_string(messageHeader->messageType_) +
                           "] and message length [" + std::to_string(messageHeader->length_) + "]");

            switch (messageHeader->messageType_) {
                case CHAT_MESSAGE:
                    boost::asio::async_read(socket_,
                                            boost::asio::buffer((void*)(buf_ + HEADER_BUFFER_SIZE), messageHeader->length_),
                                            [this](boost::system::error_code ec, std::size_t bytesTransferred) {
                        doReadChatMessage(static_cast<const ChatMessage*>((void *)buf_));
                    });
                    break;
                default:
                    logger_->info("Unknown message type [" + std::to_string(messageHeader->messageType_) + "], dropping messages");
            }
            doReadHeader();
        } else if (ec == boost::asio::error::operation_aborted || ec == boost::asio::error::eof) {
            logger_->error("Socket closed ungracefully, disconnecting: " + ec.message());
            if (socket_.is_open()) {
                socket_.shutdown(socket_.shutdown_both);
                socket_.close();
            }
        } else {
            logger_->error("Error occurred while reading header: " + ec.message());
        }
    });
}

void Server::doReadChatMessage(const ChatMessage *chatMessage) {
    logger_->info("Message received [" + std::string(chatMessage->message_) + "]");
}

void Server::doReadBody() {

}

Server::~Server() {
    logger_->info("Server destructor called");
    if (socket_.is_open()) {
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket_.close();
    }
}
