#include <iostream>
#include <fstream>
#include <filesystem>

#include "monolith.h"

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

int monolith(int argc, char** argv) {
    if(argc > 1) {
        for(s_handler handler : handlers) {
            std::string elementname = argv[1];
            if (elementname == handler.name) {
                return handler.function(argc - 1, argv + 1);
            }
        }
        std::cerr << "Usage: monolith [element name] [arguments]" << std::endl;
        return 1;
    }

    std::cout << "Monolith v" << VERSION << " - An experimental single-binary coreutils solution." << std::endl;
    std::cout << "Usage: monolith [applet name] [arguments]" << std::endl;
    std::cout << "Currently enabled Elements: " << std::endl;
    for(s_handler handler : handlers) {
        std::cout << handler.name << ": " << handler.description << std::endl;
    }
    return 0;
}

int listdir(int argc, char** argv) {
    namespace fs = std::filesystem;
    fs::path directory;
    if(argc == 1) {
        directory = fs::current_path();
    } else {
        directory = argv[1];
        if(!fs::exists(directory)){
            std::cerr << "No such file or directory [" << argv[1] << "]" << std::endl;
            return 1;
        }
    }
    std::cout << std::string{directory} << ":" << std::endl;
    for (fs::directory_entry dir_entry : fs::directory_iterator{directory}) 
        std::cout << "  " << std::string{dir_entry.path().filename()} << std::endl;
    return 0;
}

int catfile(int argc, char** argv) {
    namespace fs = std::filesystem;
    fs::path filename;
    if (argc == 1) {
        std::cerr << "Usage: cat [filename]" << std::endl;
        return 1;
    } else {
        filename = argv[1];
        if(!fs::exists(filename)){
            std::cerr << "No such file or directory [" << argv[1] << "]" << std::endl;
            return 1;
        }
        std::string currentLine;
        std::ifstream fileStream(filename);
        if(fileStream.is_open()) {
            while(getline(fileStream, currentLine)) {
                std::cout << currentLine << std::endl;
            }
            fileStream.close();
        } else {
            std::cerr << "Unable to open file." << std::endl;
            return 1;
        }
    }
    return 0;
}

int diskusage(int argc, char** argv) {
    namespace fs = std::filesystem;
    fs::path filename;
    if(argc == 1) {
        filename = fs::current_path();
    } else {
        filename = argv[1];
        if(!fs::exists(filename)) {
           std::cerr << "No such file or directory [" << argv[1] << "]" << std::endl;
           return 1;
        }
    }
    if(!fs::is_directory(filename)) {
        std::cout << "  " << std::string{filename} << "  " << fs::file_size(filename) << std::endl;
    } else {
        for (fs::directory_entry dir_entry : fs::directory_iterator{filename}) {
            if(!fs::is_directory(dir_entry.path()))
                std::cout << "  " << std::string{dir_entry.path().filename()} << "  " << fs::file_size(dir_entry.path()) << std::endl;
        }
    }
    return 0;
}