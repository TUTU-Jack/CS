#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define MAX_LEN 100

void read_Handler(void *arg)
{
    int sock = *((int*)arg);
    char buf[MAX_LEN];
    while(1)
    {
        if(read(sock,buf,MAX_LEN) == 0)
            return;
        else
            printf("Message from server:%s\n",buf);
    }
}

void write_Handler(void *arg)
{
    int sock = *((int*)arg);
    char buf[MAX_LEN];
    while(1)
    {
        fgets(buf,MAX_LEN,stdin);

        if(strcmp(buf,"Q\n") == 0 || strcmp(buf,"q\n") == 0)
        {
            shutdown(sock,SHUT_WR);
            return;
        }

        if(write(sock,buf,strlen(buf)+1) == -1)
            return;
    }
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage:%s <IP> <port>",argv[0]);
        exit(1);
    }

    pthread_t tid[2];
    int sock;
    struct sockaddr_in sock_addr;

    memset(&sock_addr,0,sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_port = htons(atoi(argv[2]));

    if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() error!");
        exit(1);
    }

    if(connect(sock,(const struct sockaddr*)&sock_addr,sizeof(sock_addr)) == -1)
    {
        perror("connect() error!");
        exit(1);
    }


    pthread_create(&tid[0],NULL,(void*)read_Handler,(void*)&sock);
    pthread_create(&tid[1],NULL,(void*)write_Handler,(void*)&sock);

    pthread_join(tid[0],0);
    pthread_join(tid[1],0);

    close(sock);

}
