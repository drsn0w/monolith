using handler_t = int (*)(int argc, char** argv);

int monolith(int argc, char** argv);
int listdir(int argc, char** argv);
int catfile(int argc, char** argv);
int diskusage(int argc, char** argv);
int yes(int argc, char** argv);
int copyfile(int argc, char** argv);
int movefile(int argc, char** argv);
int delfile(int argc, char** argv);

static const char* VERSION = "0.1a";

struct s_handler {
    const char* name;
    const handler_t   function;
    const char* description;  
};

const struct s_handler handlers[8] = {
    {"monolith",    monolith,   "The monolith binary"},
    {"ls",          listdir,    "List contents of directory"},
    {"cat",         catfile,    "Print contents of file"},
    {"du",          diskusage,  "Show disk usage of files"},
    {"yes",         yes,        "Repeatedly output a string or 'y'"},
    {"cp",          copyfile,   "Copy a file or directory"},
    {"mv",          movefile,   "Move or rename a file or directory"},
    {"rm",          delfile,    "Delete a file or directory"}
};
