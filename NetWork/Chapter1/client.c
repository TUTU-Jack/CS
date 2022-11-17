#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>


#define BUFSIZE 1024

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        printf("Usage:%s <IP> <port>\n",argv[0]);
        exit(1);
    }

    int clnt_sock,serv_sock;
    
    //创建套接字
    if((clnt_sock = socket(PF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() error!");
        exit(1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    socklen_t serv_addr_len = sizeof(serv_addr);

    //请求建立连接（客户端）
    if((serv_sock = connect(clnt_sock,(const struct sockaddr*)&serv_addr,serv_addr_len)) == -1)
    {
        perror("connetc() error!");
        exit(1);
    }

    //客户端读取数据
    char message[BUFSIZE];

    if(read(clnt_sock,&message,sizeof(message)) == -1)
    {
        perror("read() error!");
        exit(1);
    }

    printf("Message from server: %s \n",message);

    //关闭连接
    if(close(clnt_sock) == -1)
    {
        perror("close() error!");
        exit(1);
    }

    return 0;
}