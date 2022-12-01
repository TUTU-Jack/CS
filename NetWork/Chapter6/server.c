#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>

int max(int *buf)
{
    int i = 0,max = buf[0];
    int size = sizeof(buf)/sizeof(int);
    for(i = 1;i < size;i++)
    {
        if(max < buf[i])
            max = buf[i];
    }

    return max;
    
}

#define BUF_SIZE 1024
int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <port>\n",argv[0]);
        exit(1);
    }

    char buf[BUF_SIZE];
    int str_len;
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_len = sizeof(clnt_addr);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if((serv_sock = socket(PF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() error!\n");
        exit(1);
    }

    if(bind(serv_sock,(const struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind() error!\n");
        exit(1);
    }

    if(listen(serv_sock,5) == -1)
    {
        perror("listen() error!\n");
        exit(1);
    }

    int fd_max = serv_sock,fd_num;
    struct timeval timeout;
    //创建文件描述符集合
    fd_set readfds,temp;
    int i = 0;
    //集合初始化为0
    FD_ZERO(&readfds);
    //将服务器套接字描述符加入集合，监听客户端连接
    FD_SET(serv_sock,&readfds);

    while(1)
    {
        //超时处理
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
        temp = readfds;
        //加入复用
        if((fd_num = select(fd_max+1,&temp,0,0,&timeout)) == -1)
            break;
        if(fd_num == 0)
            continue;
        //遍历检查集合是否发生变化（从零检测到最大值）
        for(i = 0;i < fd_max + 1;i++)
        {
            if(FD_ISSET(i,&temp))
            {
                //服务区套接字描述符触发，表示有客户端连接
                if(i == serv_sock)
                {
                    if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len)) == -1)
                        continue;
                    fputs("client connected...",stdout);
                    //加入客户端套接字描述符
                    FD_SET(clnt_sock,&readfds);
                    if(fd_max < clnt_sock)
                        fd_max = clnt_sock;
                }
                //客户端套接字描述符触发
                else
                {
                    if((str_len = read(i,buf,BUF_SIZE)) == 0)
                    {
                        FD_CLR(i,&readfds);
                        fputs("client disconnected...",stdout);
                        close(i);
                    }
                    else
                        write(i,buf,str_len);
                }
            }

        }
        

    }

    close(serv_sock);
    return 0;
}