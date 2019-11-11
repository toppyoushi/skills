#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string.h>
using namespace std;
#define MAX_LINE 100
#define MAX_EVENTS 500
#define MAX_LISTENFD 5

int createAndListen()
{
    int on = 1;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    fcntl(listenfd, F_SETFL, O_NONBLOCK);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(11111);

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        cout << "bind error,errno:" << errno << endl;
    }

    if (listen(listenfd, MAX_LISTENFD) == -1)
    {
        cout << "listen error,errno:" << errno << endl;
    }
    return listenfd;
}

int main(int argc, char *argv[])
{
    struct epoll_event ev, events[MAX_EVENTS];
    int listenfd, connfd, sockfd;
    int readlength;
    char line[MAX_LINE];
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    int epollfd = epoll_create(1);
    if (epollfd < 0)
    {
        cout << "epoll_create error:errno" << errno << endl;
    }
    listenfd = createAndListen();
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev);

    while (1)
    {
        int fds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (fds == -1)
        {
            cout << "epoll_wait error, errno:" << errno << endl;
            break;
        }
        for (int i = 0; i < fds; ++i)
        {
            if (events[i].data.fd == listenfd)
            {
                connfd = accept(listenfd, (struct sockaddr *)&cliaddr, (socklen_t *)clilen);
                if (connfd > 0)
                {
                    cout << "new connection from "
                         << "[" << inet_ntoa(cliaddr.sin_addr)
                         << ":" << ntohs(cliaddr.sin_port) << "]"
                         << "accept socket fd" << connfd
                         << endl;
                }
                else
                {
                    cout << "accept error, connfd" << connfd
                         << "errno:" << errno << endl;
                }
                fcntl(connfd, F_SETFL, O_NONBLOCK);
                ev.data.fd = connfd;
                ev.events = EPOLLIN;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &ev) == -1)
                {
                    cout << "epoll_ctrl error, errno: " << errno << endl;
                }
            }
            else if (events[i].events & EPOLLIN)
            {
                if ((sockfd = events[i].data.fd) < 0)
                {
                    cout << "EPOLLIN sockfd < 0 error " << endl;
                    continue;
                }
                bzero(line, MAX_LINE);
                if ((readlength = read(sockfd, line, MAX_LINE)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        cout << "ECONNREST closed socket fd" << events[i].data.fd << endl;
                        close(sockfd);
                    }
                }
                else if (readlength == 0)
                {
                    cout << "read 0 closed socket fd: " << events[i].data.fd << endl;
                    close(sockfd);
                }
                else
                {
                    if (write(sockfd, line, readlength) != readlength)
                    {
                        cout << "error:not finished one time" << endl;
                    }
                }
            }
        }
    }
    return 0;
}
