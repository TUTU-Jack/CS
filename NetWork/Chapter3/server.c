#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


#define MAXNUM  5
#define BUFSIZE 1024

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1,&status,WNOHANG);
    printf("Removed proc id: %d\n",id);
}


int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usage:%s <port>\n",argv[0]);
        exit(1);
    }

    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD,&act,0);


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
    while(1)
    {

        if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size)) == -1)
            continue;
        else
            printf("Client connected.......\n");

        if((pid = fork()) == -1)
        {
            close(serv_sock);
            continue;
        }
        else if(pid == 0)
        {
            close(serv_sock);

             //接收客户端数据并回传
            while((str_len = read(clnt_sock,message,BUFSIZE)) != 0)
                write(clnt_sock,message,str_len);

            close(clnt_sock);
            printf("client disconnected....\n");

            return 0;

        }
        else
            close(clnt_sock);
    }

    close(serv_sock);

    return 0;
} 