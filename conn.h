//
// Created by Dharan Aditya on 01/02/23.
//
#include <cstdint>
#include <cstdlib>
#include "consts.h"

#ifndef REDIS_CLONE_CONN_H
#define REDIS_CLONE_CONN_H

#endif //REDIS_CLONE_CONN_H

enum {
    STATE_REQ = 0,
    STATE_RES = 1,
    STATE_END = 2
};

struct Conn {
    int fd = -1;
    uint32_t state = STATE_REQ;
    // read buffer
    size_t rbuf_size = 0;
    uint8_t rbuf[4 + K_MAX_MSG];
    // write buffers
    size_t wbuf_size = 0;
    size_t wbuf_sent = 0;
    uint8_t wbuf[4 + K_MAX_MSG];
};

void connection_io(Conn *conn);
void state_req(Conn *conn);
void state_res(Conn *conn);
bool try_fill_buffer(Conn *conn);
bool try_flush_buffer(Conn *conn);