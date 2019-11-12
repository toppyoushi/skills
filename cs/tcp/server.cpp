#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>

#define MAXLINE 4096

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    int n;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cerr << "failed to create server socket" << std::endl;
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);

    if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1)
    {
        std::cerr << "bind socket error:" << std::endl;
    }

    if (listen(listenfd, 10) == -1)
    {
        std::cerr << "listen socket error:" << std::endl;
    }

    std::cout << "waiting for requests from client..." << std::endl;
    while (1)
    {
        if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1)
        {
            std::cout << "accept error:" << std::endl;
            continue;
        }
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        std::cout << "receive message from client:" << buff << std::endl;
        close(connfd);
        break;
    }
    close(listenfd);
    return 0;
}
