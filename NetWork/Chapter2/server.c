#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAXNUM  5
#define BUFSIZE 1024

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Usage:%s <port>\n",argv[0]);
        exit(1);
    }

    char message[BUFSIZE];
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
    if(listen(serv_sock,MAXNUM) == -1)
    {
        perror("listen() error!");
        exit(1);
    }

    //接收客户端连接，建立连接
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    socklen_t str_len;

    int i = 0;
    //创建多个连接（阻塞）
    for(i = 0;i < MAXNUM;i++)
    {

        if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size)) == -1)
        {
            perror("accept() error!");
            exit(1);
        }
        else
            printf("Client connected:%d\n",i+1);

        //接收客户端数据并回传
        while((str_len = read(clnt_sock,message,BUFSIZE)) != 0)
            write(clnt_sock,message,str_len);

        close(clnt_sock);
    }

    close(serv_sock);

    return 0;
} 