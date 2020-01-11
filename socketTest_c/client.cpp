#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>

#define SERV_PORT 8088

int main(int argc,char *argv[])
{
    int sfd,len;
    struct sockaddr_in serv_addr;
    char buffer[4096];

    if(argc<2)
    {
        std::cout<<"输入服务器IP地址"<<std::endl;
        return -1;
    }

    sfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&serv_addr.sin_addr.s_addr);

    connect(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    while(true)
    {
        std::cout<<"测试1"<<std::endl;
        sprintf(buffer,"asdkhsahffd","liubi");
        std::cout<<"测试2"<<std::endl;
        write(sfd,buffer,strlen(buffer));
        std::cout<<"测试3"<<std::endl;
        len = read(sfd,buffer,sizeof(buffer));
        std::cout<<"测试4"<<std::endl;
        write(STDOUT_FILENO,buffer,len);
        std::cout<<"测试5"<<std::endl;
    }
    return 0;
}