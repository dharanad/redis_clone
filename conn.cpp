//
// Created by Dharan Aditya on 01/02/23.
//

#include <cassert>
#include <cerrno>
#include <libc.h>
#include "conn.h"
#include "utils.h"
#include "protocol.h"

void connection_io(Conn *conn) {
    if (conn->state == STATE_REQ) {
        state_req(conn);
    } else if(conn->state == STATE_RES) {
        state_res(conn);
    } else {
        msg("unknown state");
    }
}
void state_req(Conn *conn) {
    while (try_fill_buffer(conn));
}
void state_res(Conn *conn) {
    while (try_flush_buffer(conn));
}
bool try_fill_buffer(Conn *conn) {
    assert(conn->rbuf_size < sizeof(conn->rbuf));
    size_t rv = 0;
    do {
        // conn->rbuf_size -> pointer to location to fill the data
        size_t cap = sizeof(conn->rbuf) - conn->rbuf_size;
        rv = read(conn->fd, &conn->rbuf[conn->rbuf_size], cap);
    } while (rv < 0 && errno == EINTR);
    if (rv < 0 && errno == EAGAIN) {

        return false;
    }
    if (rv < 0) {
        msg("read() error");
        conn->state = STATE_END;
        return false;
    }
    if (rv == 0) {
        if (conn->rbuf_size > 0) {
            msg("unexpected EOF");
        } else {
            msg("EOF");
        }
        conn->state = STATE_END;
        return false;
    }

    conn->rbuf_size += (size_t) rv;
//    assert(conn->rbuf_size <= sizeof(conn->rbuf) - conn->rbuf_size);
    while (try_one_request(conn));
    return conn->state == STATE_REQ;
}
bool try_flush_buffer(Conn *conn) {
    size_t rv = 0;
    do {
        size_t remain = conn->wbuf_size - conn->wbuf_sent;
        rv = write(conn->fd, &conn->wbuf[conn->wbuf_sent], remain);
    } while (rv < 0);

    return true;
}
