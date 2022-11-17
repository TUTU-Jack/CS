#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1,&status,WNOHANG);
    printf("Removed proc id: %d\n",id);
}

/*
 * 1.使用两个进程，一个进程用于向客户端提供服务，另一个进程将接收到的客户端信息存储在文件中
 */
int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usage:%s <port>",argv[0]);
        exit(1);
    }

    char message[BUF_SIZE];
    char buf[BUF_SIZE];
    int str_len;

    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    memset(&clnt_addr,0,sizeof(clnt_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if((serv_sock = socket(PF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() error!");
        exit(1);
    }
    if(bind(serv_sock,(const struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind() error!");
        exit(1);
    }

    if(listen(serv_sock,5) == -1)
    {
        perror("listen() error!");
        exit(1);
    }

    pid_t pid;

    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD,&act,0);

    socklen_t clnt_addr_len = sizeof(clnt_addr);


    int fds[2];
    pipe(fds);
    FILE* fp;
    if((pid = fork()) == 0)
    {
        if((fp = fopen("file.txt","w+")) == NULL)
        {
            perror("fopen() error!");
            exit(1);
        }
        else
        {
            close(fds[1]);
            int i,len;
            for(i = 0;i < 5;i++)
            {
                len = read(fds[0],buf,BUF_SIZE);
                fwrite(buf,sizeof(char),len,fp);
            }
            
            close(fds[0]);
            fclose(fp);

            return 0;
        }
    }
    else
    {
        while(1)
        {
            if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len)) == -1)
                continue;
            else
                printf("Clinet connected....\n");

            if((pid = fork()) == 0)
            {
                close(serv_sock);
                close(fds[0]);
                while((str_len = read(clnt_sock,message,BUF_SIZE)) != 0)
                {
                    write(clnt_sock,message,str_len);
                    write(fds[1],message,str_len);
                }
                close(clnt_sock);
                close(fds[0]);
                printf("client disconnected....\n");

                return 0;
    
            }
            else
                close(clnt_sock);

        }
        
    }

    close(serv_sock);

    return 0;
}