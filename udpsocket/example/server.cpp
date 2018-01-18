#include <thread>
#include "udpsocket.h"

#define PORT 8888
#define BUFLEN 16

int main() {
    pH::netInit();

    char buf[BUFLEN];
    pH::UdpSocket udpSocket(PORT);

    std::cout << "listening for packets on port: " << PORT << std::endl;

    while(1) {
        pH::UdpMessageInfo info;
        while (udpSocket.pollDatagram(info, buf, BUFLEN)) {
            std::cout << "Received packet from "
                      << info.getAddress() << ": "
                      << info.getPort() << std::endl;
            std::cout << "Length: " << info.length << std::endl;

            if (info.length <= BUFLEN)
                buf[info.length] = '\0';
            std::cout << "Data: " << buf << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    pH::netDispose();
    return 0;
}
