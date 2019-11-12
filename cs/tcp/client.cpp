#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#define MAXSIZE 4096

int main(int argc, char *argv[])
{
    int fd;
    char sendbuff[MAXSIZE];
    char recvbuff[MAXSIZE];
    sockaddr_in servaddr;

    if (argc < 2)
    {
        std::cerr << "usage:./client <ipaddress>" << std::endl;
        return 1;
    }

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "create socket error." << std::endl;
        return 1;
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
    {
        std::cerr << "inet_pton error" << std::endl;
        return 1;
    }
    if (connect(fd, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cerr << "connect error" << std::endl;
        return 1;
    }

    std::cout << "send message to server" << std::endl;
    fgets(sendbuff, MAXSIZE, stdin);
    if (send(fd, sendbuff, MAXSIZE, 0) < 0)
    {
        std::cerr << "send error" << std::endl;
        return 1;
    }

    close(fd);
    return 0;
}