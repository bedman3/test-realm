//
// Created by martin on 5/23/21.
//

#ifndef TESTSOCKET_COMMANDPARSER_H
#define TESTSOCKET_COMMANDPARSER_H

#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>
#include "Endpoint.hpp"
#include "yaml-cpp/yaml.h"

class CommandParser {

public:
    static bool parse(int argc, const char* const argv[], std::shared_ptr<Endpoint>& serverEndpoint,
                      std::vector<std::shared_ptr<Endpoint>>& clientEndpoints);

    static bool hasNextArgument(int argc, int i);

    static bool isStringSame(const char *str1, const char *str2);

};


#endif //TESTSOCKET_COMMANDPARSER_H
