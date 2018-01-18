#ifndef PH_WIN_UDPSOCKET_H
#define PH_WIN_UDPSOCKET_H

#include <string.h>
#include <iostream>
#include <winsock2.h>
#include <unistd.h>
#include <exception>

namespace pH {

void netInit() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
}

void netDispose() { WSACleanup(); }

void setAddressIp(sockaddr_in &address, const char *ip) {
    unsigned long addr = inet_addr(ip);
    if (addr != INADDR_NONE) {
        address.sin_addr.S_un.S_addr = addr;
    } else {
        throw std::runtime_error("invalid destination ip");
    }
}

void makeSocketNonBlocking(int s) {
    long unsigned int one = 1;
    ioctlsocket(s, FIONBIO, &one);
}

void closeSocket(int s) { closesocket(s); }

using socklen_t = int;

bool checkWouldBlock() { return WSAGetLastError() == WSAEWOULDBLOCK; }

} // namespace pH

#endif // PH_WIN_UDPSOCKET_H
