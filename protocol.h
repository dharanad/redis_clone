//
// Created by Dharan Aditya on 31/01/23.
//

#include <stdlib.h>
#include <libc.h>
#include <assert.h>

#ifndef REDIS_CLONE_PROTOCOL_H
#define REDIS_CLONE_PROTOCOL_H

#endif //REDIS_CLONE_PROTOCOL_H

/*

 +-----+------+-----+------+--------
| len | msg1 | len | msg2 | more...
+-----+------+-----+------+--------

 The protocol consists of 2 parts: a 4-byte little-endian integer indicating the length of the following request,
 and a variable length request.
 */

/*
 * Reads n bytes data from the fd into buf
 * */
int32_t read_full(int fd, char* buf, size_t n);
/*
 * Writes n bytes data from the fd into buf
 * */
int32_t write_all(int fd, char* buf, size_t n);

int32_t one_request(int conn_fd);