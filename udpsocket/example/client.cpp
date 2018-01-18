#include "udpsocket.h"

#define CLIENT_PORT 8887
#define SERVER_PORT 8888
#define BUFLEN 512
#define SERVER "127.0.0.1"

int main() {
    pH::netInit();

    pH::UdpSocket udpSocket(CLIENT_PORT);
    std::string message;
    while(1) {
        printf("Enter message : ");
        std::cin >> message;

        udpSocket.sendDatagram(message.c_str(), message.size(),
                               SERVER, SERVER_PORT);
    }

    pH::netDispose();
    return 0;
}
