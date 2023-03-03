
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

/*----------------------------------------------------------------------------------------------------------------------------*/
/*     FUNCTION: recvNonBlocking
 */
/*!    \brief    It allows to receive data (recv()) as a NonBlocking function. A timeout can be set
 *
 *     \param    sockfd                        - The descriptor for the socket
 *     \param    buf                           - A pointer to a buffer where the function can store the message.
 *     \param    len                           - The size of the buffer
 *     \param    flags                         - A combination formed by ORing one or more of the values
 *     \param    timeout                       - The timeout value
 *     \param    timeout_flag                  - A flag that is set when the timeout is reached
 *
 *
 *     \returns  bytesrec                      - The number of bytes sent, or -1 if an error occurs
 *//*-------------------------------------------------------------------------------------------------------------------------*/
static ssize_t recvNonBlocking(int sockfd, void *buf, size_t len, int flags, struct timeval timeout, bool *timeout_flag)
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
        bytesrec = recv(sockfd, (char *)buf, len, flags); /*PRQA S 0315 # Justification: Message could not be solved with a cast  (void*), as this creates message 314 */
    }

    if(timeout_flag != NULL){
        *timeout_flag = timeout_tmp;
    }

    return bytesrec;
}
