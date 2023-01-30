//
// Created by Dharan Aditya on 30/01/23.
//

#ifndef REDIS_CLONE_SERVER_H
#define REDIS_CLONE_SERVER_H

#endif //REDIS_CLONE_SERVER_H
void handle_client_conn(int client_fd);
int run_server();
int bind_addr(int fd, int port);