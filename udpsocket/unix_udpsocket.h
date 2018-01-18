#ifndef PH_UNIX_UDPSOCKET_H
#define PH_UNIX_UDPSOCKET_H

#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <exception>

namespace pH {

void netInit() {}

void netDispose() {}

void setAddressIp(sockaddr_in &address, const char *ip) {
    if (inet_aton(ip , &address.sin_addr) == 0) {
        throw std::runtime_error("invalid destination ip");
    }
}

void makeSocketNonBlocking(int s) {
    int one = 1;
    ioctl(s, FIONBIO, &one);
}

void closeSocket(int s) { close(s); }

bool checkWouldBlock() { return errno == EWOULDBLOCK; }

} // namespace pH

#endif // PH_UNIX_UDPSOCKET_H
