# MetBox

A container implementation for Linux using syscalls.

### Prerequisites

- a Linux system
- a Ubuntu filesystem: https://wiki.ubuntu.com/Base

### Installing

```
    make
```

### Running
```
    ./main <cmd> <cmd params>
```

## About the project

The behaviour is very similar to what Docker, LXC and other container solutions do in the background.

I simply use a clone syscall to create a new process. For clone, I set the flags that separate the new process' root fs, host, PIDs, users and network interfaces from the parent process.

In order to use the application, you need to download a Ubuntu root filesystem - see link above.

Also, to have a separate PID space from the parent, in the new process I mount /proc. I do this because proc is not just any basic directory, but a separate pseudo-filesystem and it doesn't work without it being mounted in the child process.

## Authors

* **Alexandru Meterez**

## License

This project is licensed under the MIT License.