using handler_t = int (*)(int argc, char** argv);

int monolith(int argc, char** argv);
int listdir(int argc, char** argv);
int catfile(int argc, char** argv);
int diskusage(int argc, char** argv);

const char* VERSION = "0.1a";

struct s_handler {
    const char* name;
    handler_t   function;
    std::string description;  
};

struct s_handler handlers[4] = {
    {"monolith",    monolith,   "The monolith binary"},
    {"dir",         listdir,    "List contents of directory"},
    {"cat",         catfile,    "Print contents of file"},
    {"du",          diskusage,  "Show disk usage of files"}
};
