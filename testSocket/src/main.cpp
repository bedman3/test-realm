//
// Created by martin on 5/22/21.
//

#include <iostream>
#include <cstring>
#include "yaml-cpp/yaml.h"

class Endpoint {
    std::string host_;
    short port_;
public:
    Endpoint(std::string host, short port) : host_(host), port_(port) {}

    const std::string &getHost() { return host_; }
    short getPort() { return port_; }
};

bool hasNextArgument(int argc, int i) {
    return (argc - i > 1);
}

bool isStringSame(const char *str1, const char *str2) {
    return (std::strcmp(str1, str2) == 0);
}

int main(int argc, char *argv[]) {
    std::string configPath;
    std::shared_ptr<Endpoint> serverEndpoint;
    std::vector<std::shared_ptr<Endpoint>> clientEndpoints;

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



    return 0;
}