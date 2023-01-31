//
// Created by Dharan Aditya on 30/01/23.
//

#include <sys/socket.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "server.h"
#include "protocol.h"
#include "utils.h"

void run_server() {
    int fd = create_tcp_socket();
    if(bind_addr(fd, 8080)) {
        die("bind_addr error");
    }
    if (listen(fd, SOMAXCONN)) {
        die("listen() error");
    }
    start(fd);
}

int create_tcp_socket() {// Create a TCP/IP socket. Ref: https://beej.us/guide/bgnet/html/split/index.html
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int val = 1;
    // configure socket options
    // SO_REUSEADDR -> Bind to the same socket of the process is restarted
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    return fd;
}

void start(int fd) {
    while (TRUE) {
        struct sockaddr_in client_addr = {};
        socklen_t socklen = sizeof(client_addr);
        int conn_fd = accept(fd, (struct sockaddr*) &client_addr, &socklen);
        if (conn_fd < 0) {
            msg("accept() error");
            continue;
        }
        while (TRUE) {
            int32_t err = one_request(conn_fd);
            if (err) {
                msg("one_request() error");
                break;
            }
        }
        close(conn_fd);
    }
}

int bind_addr(int fd, int port) {
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(port);
    addr.sin_addr.s_addr = ntohl(0); // wildcard address i.e 0.0.0.1
    return bind(fd, (const struct sockaddr*) &addr, sizeof(addr));
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