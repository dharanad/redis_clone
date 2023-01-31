//
// Created by Dharan Aditya on 30/01/23.
//

#ifndef REDIS_CLONE_SERVER_H
#define REDIS_CLONE_SERVER_H

#endif //REDIS_CLONE_SERVER_H

/*
 * High level function to create a TCP Server
 * */
void run_server();

/*
 * Function to handler client connection
 * */
void handle_client_conn(int client_fd);

/*
 * Wrapper function over bind syscall to bind input port number to localhost
 * */
int bind_addr(int fd, int port);

/*
 * Start the server by accepting connection on the server fd
 * */
void start(int fd);
/*
 * Wrapper function around socket syscall to create a TCP server socket
 * */;

int create_tcp_socket();

void set_fd_nb(int fd);