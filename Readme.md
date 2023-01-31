# Redis Clone

A redis clone application build using referring this [Guide](https://build-your-own.org/redis/)

```c
                                                                                                           
Event Loop Single Thread multiplexing

+---------------------------------------------------------------------------------------------------------+
|             |            |          |           |           |           |                 |             |
| funcOne(fd1)|funcTwo(fd2)|funcX(fd1)|funcX(fd4) |  ....     |   ....    |  ............   | funcOne(fd6)|
|             |            |          |           |           |           |                 |             |
+---------------------------------------------------------------------------------------------------------+

```


```text
EPOLL Pseudo code

server_fd = create server socket
set_non_block(server_fd) 
fd_interest_list = [...]
while true:
    active_fds = poll(fd_interest_list)
    for each fd in active_fds:
        work(fd)
        
def work(fd):
    if fd is a listening socket:
        accept_client(fd)
    else fd is a client_conn:
        work_on_client(fd)

def work_on_client(fd):
    if should_read(fd):
        read & process
    while should_write(fd):
        write(fd)
    if should_close(fd):
        close(fd)   
```