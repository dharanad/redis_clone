//
// Created by Dharan Aditya on 31/01/23.
//

#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <strings.h>
#include <stdio.h>
#include "protocol.h"
#include "utils.h"

int32_t read_full(int fd, char* buf, size_t n) {
    while (n > 0) {
        ssize_t rv = read(fd, buf, n);
        if (rv <= 0) {
            return -1;
        }
        assert((size_t)rv <= n);
        n -= (size_t) rv;
        buf += rv;
    }
    return 0;
}

int32_t write_all(int fd, char* buf, size_t n) {
    while(n > 0) {
        ssize_t wv = write(fd, buf, n);
        if (wv <= 0) {
            return -1;
        }
        assert((size_t) wv <= n);
        n -= (size_t) wv;
        buf += wv;
    }
    return 0;
}

const size_t k_max_msg = 4096; // 4KB

int32_t one_request(int conn_fd) {

    char rbuf[4 + k_max_msg + 1];
    errno = 0;
    // read first four byte to rbuf
    int32_t err = read_full(conn_fd, rbuf, 4);
    if (err) {
        msg(errno == 0 ? "EOF" : "read() error");
        return err;
    }

    // copy the first four byte from rbuf to variable len
    uint32_t len = 0;
    memcpy(&len, rbuf, 4);
    if (len > k_max_msg) {
        msg("too long");
        return -1;
    }

    err = read_full(conn_fd, &rbuf[4], len);
    if (err) {
        msg("read() error");
        return err;
    }
    rbuf[4 + len] = '\0'; // terminate the string with null
    printf("client says %s\n", &rbuf[4]);


    const char reply[] = "world";
    char wbuf[4 + sizeof(reply)];
    len = (uint32_t) strlen(reply);
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], reply, len);
    return write_all(conn_fd, wbuf, 4 + len);
}