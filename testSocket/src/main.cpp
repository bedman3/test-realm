//
// Created by martin on 5/22/21.
//

#include <iostream>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async_logger.h>
#include <spdlog/async.h>
#include "CommandParser.h"
#include "Server.h"
#include "spdlog/sinks/rotating_file_sink.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<Endpoint> serverEndpoint;
    std::vector<std::shared_ptr<Endpoint>> clientEndpoints;
    std::shared_ptr<boost::asio::io_context> ioContext = std::make_shared<boost::asio::io_context>();
    spdlog::init_thread_pool(8192, 1);
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/socketApp.log", 1024 * 1024 * 50, 3);
    std::vector<spdlog::sink_ptr> sinks {stdout_sink, rotating_sink};
    auto logger = std::make_shared<spdlog::async_logger>("socketAppLogger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    logger->set_level(spdlog::level::debug);
    logger->set_pattern("[%H:%M:%S] [%^-%L-%$] [t %t] %v");
    spdlog::register_logger(logger);

    if (!CommandParser::parse(argc, argv, serverEndpoint, clientEndpoints)) {
        logger->error("Parsing error, exiting");

        return -1;
    }

    try {
        logger->info("Initializing server");

        Server server(serverEndpoint, ioContext, logger);

//        server.async_run();

        ioContext->run();
    } catch (std::exception& e) {
        logger->error("Main thread exception \n" + std::string(e.what()));
    }

    return 0;
}