# **select() API**

``` c
#include <sys/select.h>

int select(int nfds, // max file descriptor + 1, or pass FD_SETSIZE
           fd_set *restrict readfds, // fds monitored to see if ready for reading
           fd_set *restrict writefds, // fds monitored to see if ready for writing
           fd_set *restrict exceptfds, // fds monitored to see if exceptional condition occurred
           struct timeval *restrict timeout // timeout
           );
           
// Returns number of ready file descriptors, 0 on timeout, -1 on error

void FD_CLR(int fd, fd_set *set); // Removes fd from set
int  FD_ISSET(int fd, fd_set *set); // Tests if fd is in set
void FD_SET(int fd, fd_set *set); // Adds fd to set
void FD_ZERO(fd_set *set); // Removes all fds from set
```

select() allows us to monitor multiple file descriptors until one or more of them become "ready", meaning that they can perform the corresponding I/O operation whose set they are in (i.e. readfds, writefds) without blocking.
- Notes on select:
  - Instead of nfds, just pass FD_SETSIZE = 1024
  - select() can only monitor file descriptor numbers < FD_SETSIZE
  - poll() performs same function but with better API
  - select() always interrupts on signals regardless of sigaction flags
  - After select() returns, each fd_set is cleared of all file descriptors except those ready for that corresponding set. This means you must reinitalize sets before each select() call if using select() in a loop.
