#include <iostream>
#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#define BUFF_SIZE 100
using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0)
    {
        cerr << "create socket error" << errno << endl;
    }

    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(11000);

    if (bind(sock, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        cerr << "bind error:" << errno << endl;
    }
    sockaddr cliaddr;
    socklen_t socklen = sizeof(cliaddr);
    char buff[BUFF_SIZE];
    while (1)
    {
        if (recvfrom(sock, buff, BUFF_SIZE, 0, &cliaddr, &socklen) <= 0)
        {
            cerr << "receive from buffer error " << errno << endl;
            break;
        }
        sockaddr_in cliaddr_in;
        memmove(&cliaddr_in, &cliaddr, sizeof(cliaddr));
        cout << "receive from "
             << inet_ntoa(cliaddr_in.sin_addr) << ":"
             << cliaddr_in.sin_port <<endl
             << buff << endl;
    }
    close(sock);
}