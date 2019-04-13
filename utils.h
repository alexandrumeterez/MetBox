#define ENOMEM -2
#define ENEWPROC -3
#define ECMDEXEC -4

#define STACK_SIZE 65536

typedef struct parameters {
    char *command[256];
}params;