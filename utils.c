//
// Created by Dharan Aditya on 31/01/23.
//

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void msg(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

void die(const char *msg) {
    int err = errno;
    fprintf(stderr, "[%d] %s\n", err, msg);
    abort();
}
