#include <iostream>
#include <set>
#include <string>
#include <cstring>
#include "Core.hpp"

void printUsage() {
    std::cout << "Usage: ./sys_info [-lhtcrnao] \n"
              << " -l: Display ncurses mode\n"
              << " -h: Hostname\n"
              << " -t: Time info\n"
              << " -c: CPU info\n"
              << " -r: RAM info\n"
              << " -n: Network info\n"
              << " -a: Display cat\n"
              << " -o: OS info\n"
              << " --help: print usage\n";
}

bool isValidFlag(char c) {
    return std::string("lhtcrnao").find(c) != std::string::npos;
}

int main(int argc, char** argv) {
    std::set<char> displayOptions;
    Core core;

    if (argc == 2 && std::strcmp(argv[1], "--help") == 0) {
        printUsage();
        return 0;
    }

    if (argc == 1 || (argc == 2 && std::strcmp(argv[1], "-l") == 0)) {
        for (char flag : std::string("htcrnao")) {
            displayOptions.insert(flag);
        }
        if (argc == 2) displayOptions.insert('l');
    } else {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg.size() < 2 || arg[0] != '-') {
                printUsage();
                return 2;
            }

            for (size_t j = 1; j < arg.size(); ++j) {
                char flag = arg[j];
                if (!isValidFlag(flag)) {
                    printUsage();
                    return 1;
                }
                displayOptions.insert(flag);
            }
        }
    }

    char optionsArray[SIZE_OPT] = {0};
    size_t index = 0;
    for (char flag : displayOptions) {
        if (index < SIZE_OPT) {
            optionsArray[index++] = flag;
        }
    }

    core.start(optionsArray);
    return 0;
}
