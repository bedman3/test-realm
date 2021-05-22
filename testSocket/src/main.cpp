//
// Created by martin on 5/22/21.
//

#include <iostream>
#include <cstring>

bool hasNextArgument(int argc, int i) {
    return (argc - i > 1);
}

bool isStringSame(const char* str1, const char* str2) {
    return (std::strcmp(str1, str2) == 0);
}

int main(int argc, char* argv[]) {
    std::string configPath;

    for (int i = 0; i < argc; ++i) {
        if (isStringSame(argv[i], "--configPath") && hasNextArgument(argc, i)) {
            configPath = std::string(argv[++i]);
        }
    }

    std::cout << "configPath is [" << configPath << "]" << std::endl;

    return 0;
}