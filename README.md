# NoBlockingReceive
It allows to receive data (recv()) as a NonBlocking function. A timeout can be set

Synopsis:
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

ssize_t recvNonBlocking(int sockfd,
                        void *buf,
                        size_t len,
                        int flags,
                        struct timeval timeout,
                        bool *timeout_flag)
Arguments:

  sockfd:
    The descriptor for the socket
  buf:
    A pointer to a buffer where the function can store the message.
  len:
    The size of the buffer
  flags:
    A combination formed by ORing one or more of the values
  timeout:
    The timeout value
  timeout_flag:
    A flag that is set when the timeout is reached
  
 Returns:
    The number of bytes sent, or -1 if an error occurs

