using handler_t = int (*)(int argc, char** argv);

int monolith(int argc, char** argv);
int listdir(int argc, char** argv);
int catfile(int argc, char** argv);
int diskusage(int argc, char** argv);

struct s_handler {
    const char* name;
    handler_t   function;  
};

struct s_handler handlers[4] = {
    {"monolith",    monolith},
    {"dir",         listdir},
    {"cat",         catfile},
    {"du",          diskusage}
};
