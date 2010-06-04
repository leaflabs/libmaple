#ifndef _SOCKET_H_
#define _SOCKET_H_

/**
 *  @brief socket operations
 */

#ifdef __cplusplus
extern "C"{
#endif


enum sock_type {
   SOCK_STREAM  = 0x1,
   SOCK_DGRAM   = 0x2
};

int32 socket(int32 type);
int32 bind(int32 sockfd, uint16 port);
int32 listen(int32 sockfd);

#ifdef __cplusplus
}
#endif

#endif

