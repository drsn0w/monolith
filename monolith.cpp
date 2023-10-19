#include <iostream>
#include <fstream>
#include <filesystem>

#include "monolith.h"

struct s_handler element_handlers[] = {
    {"monolith",    monolith,   "The monolith binary"},
    {"ls",          listdir,    "List contents of directory"},
    {"cat",         catfile,    "Print contents of file"},
    {"du",          diskusage,  "Show disk usage of files"},
    {"yes",         yes,        "Repeatedly output a string or 'y'"},
    {"cp",          copyfile,   "Copy a file or directory"},
    {"mv",          movefile,   "Move or rename a file or directory"},
    {"rm",          delfile,    "Delete a file or directory"},
};

size_t element_handler_count = sizeof(element_handlers) / sizeof(element_handlers[0]);

int monolith(int argc, char** argv) {
    if(argc > 1) {
        for(s_handler handler : element_handlers) {
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
    for(s_handler handler : element_handlers) {
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

int yes(int argc, char** argv) {
    std::string string;
    if (argc == 1) string = 'y';
    else string = argv[1];

    while(true) {
        std::cout << string << std::endl;
    }

    return 0;
}

int copyfile(int argc, char** argv) {
    namespace fs = std::filesystem;
    if (argc != 3) {
        std::cerr << "Usage: cp [source file] [destination file]" << std::endl;
        return 1;
    }
    fs::path sourceFile = argv[1];
    fs::path destFile = argv[2];
    if(!fs::exists(sourceFile)) {
        std::cerr << "No such file or directory [" << sourceFile << "]" << std::endl;
        return 1;
    }
    fs::copy(sourceFile, destFile, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
    return 0;
}

int movefile(int argc, char** argv) {
    namespace fs = std::filesystem;
    if (argc != 3) {
        std::cerr << "Usage: mv [source file] [destination file]" << std::endl;
        return 1;
    }
    fs::path sourceFile = argv[1];
    fs::path destFile = argv[2];
    if(!fs::exists(sourceFile)) {
        std::cerr << "No such file or directory [" << sourceFile << "]" << std::endl;
        return 1;
    }
    if(fs::exists(destFile)) {
        std::cerr << "File or directory already exists [" << destFile << "]" << std::endl;
    }
    fs::rename(sourceFile, destFile);
    return 0;
}

int delfile(int argc, char** argv) {
    namespace fs = std::filesystem;
    if (argc == 1) {
        std::cerr << "Usage: rm [filename]" << std::endl;
        return 1;
    }
    fs::path filename = argv[1];
    if(!fs::exists(filename)) {
        std::cerr << "No such file or directory [" << filename << "]" << std::endl;
        return 1;
    }
    fs::remove_all(filename);
    return 0;
}