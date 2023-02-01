//
// Created by Dharan Aditya on 31/01/23.
//

#include <cerrno>
#include <cstdlib>
#include <libc.h>
#include <cassert>
#include "protocol.h"
#include "utils.h"
#include "consts.h"

int32_t read_full(int fd, char *buf, size_t n) {
    while (n > 0) {
        ssize_t rv = read(fd, buf, n);
        if (rv <= 0) {
            return -1;
        }
        assert((size_t) rv <= n);
        n -= (size_t) rv;
        buf += rv;
    }
    return 0;
}

int32_t write_all(int fd, char *buf, size_t n) {
    while (n > 0) {
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

int32_t one_request(int conn_fd) {

    char rbuf[4 + K_MAX_MSG + 1];
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
    if (len > K_MAX_MSG) {
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

bool try_one_request(Conn *conn) {
    // try parsing request from the buffer
    if (conn->rbuf_size < 4) {
        return 4;
    }
    uint32_t len = 0;
    memcpy(&len, &conn->rbuf[0], 4);
    if (len > K_MAX_MSG) {
        msg("too long");
        conn->state = STATE_END;
        return false;
    }
    if (4 + len > conn->rbuf_size) {
        return false;
    }
    printf("client says: %s\n", &conn->rbuf[4]);

    // echoing in the response
    memcpy(&conn->wbuf[0], &len, 4);
    memcpy(&conn->wbuf[4], &conn->rbuf[4], len);
    conn->wbuf_size = 4 + len;

//    size_t remain = conn->rbuf_size - 4 - len;
//    if (remain) {
//        memmove(conn->rbuf, &conn->rbuf[4 + len], remain);
//    }
//    conn->rbuf_size = remain;

    conn->state = STATE_RES;
    state_res(conn);
    return conn->state = STATE_REQ;
}