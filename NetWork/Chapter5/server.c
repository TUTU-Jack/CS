#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define MAX_NUM 256
#define MAX_LEN 100

int clnt_sock_buf[MAX_NUM];
int clnt_cnt;

pthread_mutex_t mutex;

void socket_handler(void *arg)
{
    int sock = *((int*)arg);
    int str_len = 0,index = 0;
    char buf[MAX_LEN];
    while((str_len = read(sock,buf,MAX_LEN)) != 0)
    {
        if(write(sock,buf,str_len) == -1)
        {
            perror("write error()!");
            return;
        }
    }

    pthread_mutex_lock(&mutex);
    for(index = 0;index < clnt_cnt;index++)
    {
        if(sock == clnt_sock_buf[index])
        {
            while(index++ < clnt_cnt - 1)
                clnt_sock_buf[index] = clnt_sock_buf[index+1];
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutex);
    close(sock);
    puts("Client disconnected...");
}

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("Usage:%s <port>",argv[0]);
        exit(1);
    }
    int index = 0;
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    socklen_t clnt_addr_len = sizeof(clnt_addr);

    pthread_t tid[MAX_NUM];
    pthread_t* ptid = tid;

    pthread_mutex_init(&mutex,NULL);

    if((serv_sock = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() error!");
        exit(1);
    }

    if(bind(serv_sock,(const struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind() error!");
        exit(1);
    }

    if(listen(serv_sock,MAX_NUM) == -1)
    {
        perror("listen() error!");
        exit(1);
    }

    while(1)
    {
        if((clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len)) == -1)
            continue;
        else
        {
            pthread_mutex_lock(&mutex);
            clnt_sock_buf[clnt_cnt++] = clnt_sock;
            pthread_mutex_unlock(&mutex);

            puts("Client connected...");
            //新的连接创建线程
            pthread_create(ptid,NULL,(void*)socket_handler,(void*)&clnt_sock);
            pthread_detach(*ptid);
            ptid++;
        }
    }

    close(serv_sock);
    return 0;
}
