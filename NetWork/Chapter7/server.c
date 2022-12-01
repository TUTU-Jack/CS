#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/poll.h>

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
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    socklen_t clnt_addr_len = sizeof(clnt_addr);

    if((serv_sock = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() errror!");
        exit(1);
    }

    if(bind(serv_sock,(const struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind() error!");
        exit(1);
    }

    if(listen(serv_sock,1) == -1)
    {
        perror("listen() error!");
        exit(1);
    }

    int count = 0,i = 0;
    //创建 poll 监听数组
    struct pollfd fds[BUF_SIZE];
    //将服务器套接字描述符加入监听
    fds[0].fd = serv_sock;
    //监听事件为输入
    fds[0].events = POLLIN;
    //返回结果
    fds[0].revents = 0;
    int ret;

    while(1)
    {  
        //开始监听
        if((ret = poll(fds,count+1,1000)) == -1)
            break;
        if(ret == 0)
            continue;
        //轮询监听返回值
        for(i = 0;i < count+1;i++)
        {
            //客户端套接字断开或套接字发生错误
            if(fds[i].revents & POLLRDHUP || fds[i].revents & POLLERR)
            {
                //将该描述符替换为最后一个描述符
                fds[i] = fds[count];
                close(fds[i].fd);
                //监听数量减1
                count--;
            }
            //服务器端套接字返回读（有客户端请求连接）
            else if(fds[i].fd == serv_sock && fds[i].revents & POLLIN)
            {
                if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len)) == -1)
                    continue;
                fputs("Client connected...",stdout);
                
                //将客户端加入数组
                fds[++count].fd = clnt_sock;
                fds[count].events = POLLIN | POLLERR;
                fds[count].revents = 0;
            }
            //客户端状态
            else if(fds[i].revents & POLLIN)
            {
                if((str_len = read(fds[i].fd,buf,BUF_SIZE)) == 0)
                {
                    fputs("Client disconnected...",stdout);
                    fds[i] = fds[count];
                    close(fds[i].fd);
                    count--;
                }
                write(fds[i].fd,buf,str_len);
                //清除返回值，监听下次状态
                fds[i].revents &= ~POLLIN;
            }

        }

    }

    close(serv_sock);

    return 0;
}


