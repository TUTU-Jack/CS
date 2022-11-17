#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usage:%s <port>\n",argv[0]);
        exit(1);
    }

    const char* message = "Hello World!";
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
   
    //创建套接字
    if((serv_sock = socket(PF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() error!");
        exit(1);
    }
    memset(&serv_addr,0,sizeof(serv_addr));

    //套接字 协议簇 IP地址 应用程序端口号
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    //分配套接字IP/Port
    if(bind(serv_sock,(const struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind() error!");
        exit(1);
    }

    //监听客户端连接
    if(listen(serv_sock,1) == -1)
    {
        perror("listen() error!");
        exit(1);
    }

    //接收客户端连接，建立连接
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    
    if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size)) == -1)
    {
        perror("accept() error!");
        exit(1);
    }

    //向客户端发送数据
    if(write(clnt_sock,message,strlen(message)) == -1)
    {
        perror("write() error!");
        exit(1);
    }

    //关闭连接
    if(close(clnt_sock) == -1 || close(serv_sock) == -1)
    {
        perror("close() error!");
        exit(1);
    }

    return 0;
} 