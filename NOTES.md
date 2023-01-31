# Notes


#### SO_REUSEADDR Flag
Allows other sockets to bind() to this port, unless there is an active listening socket bound to the port already.
This enables you to get around those “Address already in use” error messages when you try to restart your server
after a crash.

## Syscall

#### ntohs & ntohl
Convert multi-byte integer types from host byte order to network byte order
* ntohs -> network to host short
* ntohl -> network to host long

#### perror
many functions return -1 on error and set the value of the variable errno to be some number,
it would sure be nice if you could easily print that in a form that made sense to you.

#### read
read() attempts to read up to count bytes from file descriptor fd
into the buffer starting at buf.

[C Typecasting](https://stackoverflow.com/questions/21099041/why-do-we-cast-sockaddr-in-to-sockaddr-when-calling-bind)