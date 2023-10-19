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

extern struct s_handler element_handlers[];
extern size_t element_handler_count;
