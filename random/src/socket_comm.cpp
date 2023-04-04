#include "socket_comm.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

socket_comm::socket_comm(const std::string& host, int port, bool isClient) :
    host_(host),
    port_(port) {
    std::string loggerName = std::string((isClient ? "client" : "server")) + "-" + host_ + ":" + std::to_string(port);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);
    console_sink->set_pattern("[%H:%M:%S] [%n] [%^-%L-%$] [t-%t] %v");
    logger_ = std::make_unique<spdlog::logger>(loggerName, console_sink);

    logger_->info(std::string() + "Created socket [" + (isClient ? "client" : "server") + "] with host ip [" + host_ + "] and port [" + std::to_string(port) + "]");
//    logger_.flush();
}