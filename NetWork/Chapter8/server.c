#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int setNoBlock(int sock)
{
    int flag = fcntl(sock,F_GETFL);
    flag = flag | O_NONBLOCK;
    return fcntl(sock,F_SETFL,flag);
}

#define MAX_LEN 1024
#define MAX_SIZE 1024

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <port>\n",argv[0]);
        exit(1);
    }

    char buffer[MAX_LEN];
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

    setNoBlock(serv_sock);

    int count = 0,i = 0;
    struct epoll_event event,events[MAX_SIZE];
    int efd = epoll_create(MAX_SIZE);
    event.data.fd = serv_sock;
    event.events = EPOLLIN;
    epoll_ctl(efd,EPOLL_CTL_ADD,serv_sock,&event);

    while(1)
    {
        int nfd = epoll_wait(efd,events,MAX_SIZE,1000);
        for(i = 0;i < nfd;i++)
        {
            if(events[i].events & EPOLLRDHUP || events[i].events & EPOLLERR)
            {
                epoll_ctl(efd,EPOLL_CTL_DEL,events[i].data.fd,&event);
                close(events[i].data.fd);
                puts("Client disconnected...");
            }

            else if(events[i].data.fd == serv_sock && events[i].events & EPOLLIN)
            {
                if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len)) == -1)
                    continue;
                puts("Client connected...");
                setNoBlock(clnt_sock);
                event.data.fd = clnt_sock;
                event.events = EPOLLIN | EPOLLERR;
                epoll_ctl(efd,EPOLL_CTL_ADD,clnt_sock,&event);
            }
            else if(events[i].events & EPOLLIN)
            {
                if((str_len = read(events[i].data.fd,buffer,MAX_LEN)) == 0)
                {
                    epoll_ctl(efd,EPOLL_CTL_DEL,events[i].data.fd,&event);
                    close(events[i].data.fd);
                    puts("Client disconnected...");
                }
                write(events[i].data.fd,buffer,str_len);
            }
        }

    }

    close(serv_sock);
    return 0;
}
