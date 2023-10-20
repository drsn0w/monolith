#include <iostream>
#include <fstream>
#include <filesystem>

#include "include/monolith.h"

int main(int argc, char** argv) {

    if (argc == 0) return 1;
    std::string basename = std::filesystem::path(argv[0]).filename();

    for(s_handler handler : handlers) {
        if (handler.name == basename) {
            return handler.function(argc, argv);
        }
    } 
    return 0;
}