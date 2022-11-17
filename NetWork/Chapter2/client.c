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

    char message[BUFSIZE];
    size_t str_len;

    //客户端写数据
    while(1)
    {
        fputs("Input Message(Q to quit):",stdout);
        fgets(message,BUFSIZE,stdin);

        if(!strcmp((const char*)message,"Q\n") || !strcmp((const char*)message,"q\n"))
            break;

        //客户端向服务器端写数据
        if(write(clnt_sock,message,strlen(message)+1) == -1)
        {
            perror("write() error!");
            exit(1);
        }

        //客户端回读服务器端数据
        if((str_len = read(clnt_sock,message,BUFSIZE)) == -1)
        {
            perror("read() error!");
            exit(1);
        }
        else
            printf("Message from server: %s",message);

    }

    close(clnt_sock);


    return 0;
}