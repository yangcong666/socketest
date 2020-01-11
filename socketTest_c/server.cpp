#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

# define SERV_PORT 8088

int main(int argc,char *argv[])
{
    int sfd,cfd;
    int i,len;
    struct sockaddr_in serv_addr,client_addr;
    char buffer[4096],client_ip[128];
    socklen_t addr_len;

    // 建立socket套记住
    sfd = socket(AF_INET,SOCK_STREAM,0);

    //绑定地址
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    // 监听套接字
    listen(sfd,256);
    std::cout<<"监听开始了"<<std::endl;

    // 接受请求连接
    addr_len = sizeof(client_addr);
    cfd = accept(sfd,(struct sockaddr *)&client_addr,&addr_len);
    std::cout<<"连接成功，IP地址为："<<inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,
    client_ip,sizeof(client_ip))<<"端口号："<<ntohs(client_addr.sin_port);

    while(true)
    {
        len = read(cfd,buffer,sizeof(buffer));
        sprintf(buffer,"这是服务器","liubi");
        write(STDOUT_FILENO,buffer,len);
        write(cfd,buffer,len);
    }
    close(cfd);
    close(sfd);
    return 0;


}