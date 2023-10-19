#include <iostream>
#include <fstream>
#include <filesystem>

#include "monolith.h"

int main(int argc, char** argv) {

    if (argc == 0) return 1;
    std::string basename = std::filesystem::path(argv[0]).filename();

    for(size_t i = 0; i < element_handler_count; i++) {
        s_handler &handler = element_handlers[i];

        if (handler.name == basename) {
            return handler.function(argc, argv);
        }
    }
    return 0;
}