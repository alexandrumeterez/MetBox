//test
// docker run image <cmd> <params>
// ./main run       <cmd> <params>
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#define _GNU_SOURCE  
#include <linux/sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mount.h>

int fn(void *arg) {
    pid_t mypid = getpid();
    printf("Running as %d\n", mypid);
    
    // Change hostname of the container
    char hostname[] = "container";
    sethostname(hostname, strlen(hostname));

    // Change root of the container
    char rootfs[] = "/home/alex/basic_container/ubuntu_fs";
    chroot(rootfs);
    chdir("/");
    mount("proc", "proc", "proc", 0, "");

    params p = *((params*)arg);
    execvp(p.command[0], p.command);

    return 0;   
}

int run(int argc, char *argv[]) {
    pid_t mypid = getpid();
    printf("Running as %d\n", mypid);

    char *command[argc];
    for(int i = 0; i < argc - 2; ++i) {
        command[i] = argv[i+2];
    }
    command[argc - 2] = NULL;


    // Send params to child function
    params p;
    for(int i = 0; i < argc; ++i) {
        p.command[i] = command[i];
    }

    // Allocate stack for the process
    char *stack = (char*)malloc(STACK_SIZE);

    // Launch child process
    pid_t pid = clone(fn, stack + STACK_SIZE, CLONE_NEWUTS | CLONE_NEWPID | SIGCHLD, &p);
    waitpid(pid, NULL, 0);

    return 0;
}

int main(int argc, char *argv[]) {
    int retval;
    if(argc == 1) {
        printf("Usage: %s run <cmd> <params>\n", argv[0]);
        return -1;
    }

    if(strcmp(argv[1], "run") != 0) {
        printf("Usage: %s run <cmd> <params>\n", argv[0]);
        return -1;
    }
    else {
        retval = run(argc, argv);
        if(retval == -1) {
            return -1;
        }
    }
    

}
