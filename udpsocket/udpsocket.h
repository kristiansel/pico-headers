#ifndef PH_UDPSOCKET_H
#define PH_UDPSOCKET_H

#ifdef _WIN32
#include "win_udpsocket.h"
#elif __unix
#include "unix_udpsocket.h"
#endif

namespace pH {

sockaddr_in createAddress(uint16_t port, const char *ip = nullptr) {
    sockaddr_in address;
    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (ip) {
        setAddressIp(address, ip);
    } else {
        address.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    return address;
}

struct UdpMessageInfo {
    ssize_t length;
    sockaddr_in address;

    const char *getAddress() { return inet_ntoa(address.sin_addr); }
    uint16_t getPort() { return ntohs(address.sin_port); }
};

class UdpSocket {
    int s;

    UdpSocket() = delete;
public:
    UdpSocket(uint16_t port) {
        if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
            throw std::runtime_error("Could not create socket");
        }

        makeSocketNonBlocking(s);

        if (port != 0) {
            sockaddr_in address = createAddress(port);
            if(bind(s, reinterpret_cast<const sockaddr*>(&address),
                    sizeof(address)) == -1)
            {
                closeSocket(s);
                throw std::runtime_error("could not bind socket");
            }
        }
    }

    ~UdpSocket() {
        closeSocket(s);
    }

    bool pollDatagram(UdpMessageInfo &info, char *buffer, size_t bufferSize) {
        socklen_t slen = sizeof(info.address);
        info.length = recvfrom(s, buffer, bufferSize, 0,
                               reinterpret_cast<sockaddr*>(&info.address),
                               &slen);
        if (info.length < 0 && !checkWouldBlock()) {
            throw std::runtime_error("failed to receive from socket");
        }
        return info.length > 0;
    }

    void sendDatagram(const char *buffer, size_t bufferSize,
                      const char *ip, uint16_t port)
    {
        sockaddr_in si_other = createAddress(port, ip);
        if (sendto(s, buffer, bufferSize, 0,
                   reinterpret_cast<sockaddr *>(&si_other),
                   sizeof(sockaddr_in))==-1)
        {
            throw std::runtime_error("could not send from socket");
        }
    }
};

} // namespace pH

#endif // PH_UDPSOCKET_H
