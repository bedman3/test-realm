//
// Created by martin on 5/23/21.
//

#include <iostream>
#include "CommandParser.hpp"

bool CommandParser::parse(int argc, const char* const argv[], std::shared_ptr <Endpoint>& serverEndpoint,
                          std::vector <std::shared_ptr<Endpoint>>& clientEndpoints) {
    if (argc < 2) {
        std::cout << "no arguments, exiting" << std::endl;
        return false;
    }

    std::string configPath;
    for (int i = 0; i < argc; ++i) {
        if (isStringSame(argv[i], "--configPath") && hasNextArgument(argc, i)) {
            configPath = std::string(argv[++i]);
        }
    }

    try {
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

        std::cout << "Finished loading config" << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Error loading config \n" << e.what() << std::endl;
        return false;
    }

    return true;
}

bool CommandParser::hasNextArgument(int argc, int i) {
    return (argc - i > 1);
}

bool CommandParser::isStringSame(const char *str1, const char *str2) {
    return (std::strcmp(str1, str2) == 0);
}