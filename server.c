//
// Created by Dharan Aditya on 30/01/23.
//

#include <sys/socket.h>
#include <netinet/tcp.h>
#include <libc.h>
#include "server.h"


void accept_connections(int fd);

int create_tcp_socket();

int run_server() {
    int fd = create_tcp_socket();
    if(bind_addr(fd, 8080)) {
        perror("bind_addr");
        exit(-1);
    }
    if (listen(fd, SOMAXCONN)) {
        perror("listen");
        exit(-2);
    }
    accept_connections(fd);
    return 0;
}

int create_tcp_socket() {// Create a TCP/IP socket. Ref: https://beej.us/
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int val = 1;
    // configure socket options
    // SO_REUSEADDR -> Bind to the same socket of the process is restarted
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    return fd;
}

void accept_connections(int fd) {
    while (TRUE) {
        struct sockaddr_in client_addr = {};
        socklen_t socklen = sizeof(client_addr);
        int conn_fd = accept(fd, (struct sockaddr*) &client_addr, &socklen);
        if (conn_fd < 0) {
            perror("accept");
            continue;
        }
        handle_client_conn(conn_fd);
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

void handle_client_conn(int client_fd) {
    char buf[64] = {}; // 64 bytes buffer
    size_t n = read(client_fd, buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("handle_client_conn");
        return;
    }
    printf("client says: %s\n", buf);
    char* reply = "foo reply\n";
    write(client_fd, reply, strlen(reply));
}
