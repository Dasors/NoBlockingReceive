
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

ssize_t recvNBlocking(int sockfd, void *buf, size_t len, int flags, struct timeval timeout, bool *timeout_flag)
{
    ssize_t bytesrec=0;
    bool timeout_tmp = false;

    fd_set fds;
    int n;

    /*set up the file descriptor set*/
    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);

    /*wait until timeout or data received*/
    n = select(sockfd + 1, &fds, NULL, NULL, &timeout);

    /* timeout*/
    if (n == 0){
        bytesrec = 0;
        timeout_tmp = true;
    }
    /* error*/
    else if (n == -1){
        bytesrec = -1;
    }
    /*ready to read*/
    else
    {
        bytesrec = recv(sockfd, (char *)buf, len, flags);
    }

    if(timeout_flag != NULL){
        *timeout_flag = timeout_tmp;
    }

    return bytesrec;
}
