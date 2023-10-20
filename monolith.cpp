#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>

#include "include/monolith.h"
#include "include/utils.h"

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
        std::cout << "  " << std::string{dir_entry.path()} << std::endl;
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

    bool human_readable = false;

    int opt;
    opterr = 0;
    while((opt = getopt(argc, argv, "h")) != -1) {
        switch(opt) {
            case 'h':
                human_readable = true;
                break;
            default:
                std::cerr << "Unknown argument -" << char(optopt) << std::endl << "Usage: du [filename]" << std::endl;
        }
    }

    fs::path filename;
    if(optind >= argc) {
        filename = fs::current_path();
    } else {
        filename = argv[optind];
        if(!fs::exists(filename)) {
           std::cerr << "No such file or directory [" << argv[1] << "]" << std::endl;
           return 1;
        }
    }
    if(!fs::is_directory(filename)) {
        if(human_readable) std::cout << std::left << std::setw(10) << bytes_to_hr(fs::file_size(filename), 1) << std::string{filename} << std::endl;
        else std::cout << std::left << std::setw(10) << fs::file_size(filename) << std::string {filename} << std::endl;
        
        
    } else {
        for (fs::directory_entry dir_entry : fs::directory_iterator{filename}) {
            if(!fs::is_directory(dir_entry.path()))
                if(human_readable) std::cout << std::left << std::setw(10) << bytes_to_hr(fs::file_size(dir_entry.path()), 1) << std::string{dir_entry.path().filename()} << std::endl;
                
                else std::cout << std::left << std::setw(10) << fs::file_size(dir_entry.path()) << std::string{dir_entry.path().filename()} << std::endl;;
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

    int recursive = 0;
    int force = 0;
    int verbose = 0;

    // parse arguments
    int opt;
    opterr = 0;
    while((opt = getopt(argc, argv, "rfv")) != -1) {
        switch(opt) {
            case 'r':
                recursive = 1;
                break;
            case 'f':
                force = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                std::cout << "Unknown argument -" << char(optopt) << std::endl << "Usage: rm [filename]" << std::endl;
                return 1;
        }
    }

    if(optind >= argc) {
        std::cout << "Usage: rm [filename]" << std::endl;
        return 1;
    }

    fs::path filename = argv[optind];

    if(!fs::exists(filename)) {
        std::cerr << "No such file or directory [" << filename << "]" << std::endl;
        return 1;
    }

    if(recursive && force) {
        fs::remove_all(filename);
        if(verbose) std::cout << "rm: removing " << filename << std::endl;
        return 0;
    }

    fs::remove(filename);
    if(verbose) std::cout << "rm: removing " << filename << std::endl;

    return 0;
}