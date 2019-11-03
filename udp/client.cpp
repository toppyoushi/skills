#include <iostream>
#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(11000);

    if(connect(sock,(sockaddr*)&servaddr,sizeof(sockaddr))<0)
    {
        cerr<<"connect error:"<<errno<<endl;
    }

    char buff[BUFF_SIZE];
    while (cin >> buff)
    {
        ssize_t n = sendto(sock,buff,BUFF_SIZE,0,(sockaddr*)&servaddr,sizeof(servaddr));
        if (n<=0)
        {
            cerr << "send to buffer error " << errno << endl;
            break;
        }
        cout<<"send successfully..."<<endl;
    }
    close(sock);
}
