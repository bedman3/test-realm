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
        logger_(logger)
        {
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    async_run();
}

void Server::async_run() {
    logger_->info("Server accepting socket at endpoint [" + Utility::to_string(acceptor_.local_endpoint()) + "]");
    acceptor_.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            std::shared_ptr<boost::asio::ip::tcp::socket> socketPtr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(socket));
            socketVector_.push_back(socketPtr);
            logger_->info("Socket connected with remote client [" + Utility::to_string(socketPtr->remote_endpoint()) + "]");

            if (!ec) {
                doReadHeader(socketPtr);
            } else {
                logger_->error("Error occurred while accepting socket: " + ec.message());
            }

            async_run();
        }
    );
}

void Server::doReadHeader(std::shared_ptr<boost::asio::ip::tcp::socket> socketPtr) {
    boost::asio::async_read(*socketPtr,
                            boost::asio::buffer(buf_, HEADER_BUFFER_SIZE),
                            [this, socketPtr](boost::system::error_code ec, std::size_t bytesTransferred) {
        logger_->debug("Socket read header bytes [" + std::to_string(bytesTransferred) + "]");
        if (!ec) {
            const MessageHeader* messageHeader = static_cast<const MessageHeader*>((void *)this->buf_);
            logger_->debug("Received message with message type [" + std::to_string(messageHeader->messageType_) +
                           "] and message length [" + std::to_string(messageHeader->length_) + "]");

            switch (messageHeader->messageType_) {
                case MessageType::CHAT_MESSAGE:
                    boost::asio::async_read(*socketPtr,
                                            boost::asio::buffer((void*)(buf_ + HEADER_BUFFER_SIZE), messageHeader->length_),
                                            [this, socketPtr](boost::system::error_code ec, std::size_t bytesTransferred) {
                        doReadChatMessage(static_cast<const ChatMessage*>((void *)buf_), socketPtr);
                    });
                    break;
                default:
                    logger_->info("Unknown message type [" + std::to_string(messageHeader->messageType_) + "], dropping messages");
            }
            doReadHeader(socketPtr);
        } else if (ec == boost::asio::error::eof) {
            logger_->info("Socket [" + Utility::to_string(socketPtr->remote_endpoint()) + "] closed, disconnecting: " + ec.message());
            if (socketPtr->is_open()) {
                socketPtr->shutdown(socketPtr->shutdown_both);
                socketPtr->close();
            }
        } else {
            logger_->error("Error occurred while reading header: " + ec.message());
        }
    });
}

void Server::doReadChatMessage(const ChatMessage *chatMessage, const std::shared_ptr<boost::asio::ip::tcp::socket>& socketPtr) {
    logger_->info("[" + Utility::to_string(socketPtr->remote_endpoint()) + "] Message received [" + chatMessage->message_ + "]");
}

void Server::doReadBody() {

}

Server::~Server() {
    logger_->info("Server destructor called");
    std::for_each(socketVector_.begin(), socketVector_.end(),
                  [](std::shared_ptr<boost::asio::ip::tcp::socket>& socket) {
                      if (socket->is_open()) {
                          socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                          socket->close();
                      }
                  });
}
