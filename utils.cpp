//
// Created by Dharan Aditya on 31/01/23.
//

#include <libc.h>
#include <cerrno>

void msg(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

void die(const char *msg) {
    int err = errno;
    fprintf(stderr, "[%d] %s\n", err, msg);
    abort();
}

void set_fd_nb(int fd) {
    errno = 0;
    int flags = fcntl(fd, F_GETFL, 0);
    if (errno) {
        die("fcntl error");
        return;
    }
    flags |= O_NONBLOCK;

    errno = 0;
    fcntl(fd, flags, 0);
    if (errno) {
        die("fcntl error");
        return;
    }
}