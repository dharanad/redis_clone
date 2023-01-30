Ref
setsockopt syscall

SO_REUSEADDR
Allows other sockets to bind() to this port, unless there is an active listening socket bound to the port already.
This enables you to get around those “Address already in use” error messages when you try to restart your server
after a crash.

ntohs & ntohl syscall
Convert multi-byte integer types from host byte order to network byte order
ntohs -> network to host short
ntohl -> network to host long

perror
many functions return -1 on error and set the value of the variable errno to be some number,
it would sure be nice if you could easily print that in a form that made sense to you.