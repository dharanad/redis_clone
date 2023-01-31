//
// Created by Dharan Aditya on 31/01/23.
//

#include <cstdint>
#include <cstdlib>
#include "consts.h"

#ifndef REDIS_CLONE_EL_H
#define REDIS_CLONE_EL_H

enum {
    STATE_REQ = 0,
    STATE_RES = 1,
    STATE_END = 2
};

struct Conn {
    int fd;
    uint32_t state;
    // read buffer
    size_t rbuf_size;
    uint8_t rbuf[4 + K_MAX_MSG];
    // write buffers
    size_t wbuf_size;
    size_t wbuf_sent;
    uint8_t wbuf[4 + K_MAX_MSG];
};

#endif //REDIS_CLONE_EL_H
