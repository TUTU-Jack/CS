#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LEN 100

void write_message_proc(int sock,char* message,int size)
{
    while(1)
    {
        //fputs("Input Message(Q to exit):",stdout);
        fgets(message,size,stdin);

        if(strcmp(message,"Q\n") == 0 || strcmp(message,"q\n") == 0)
        {
            shutdown(sock,SHUT_WR);
            return;
        }

        if(write(sock,message,strlen(message)+1) == -1)
            return;
    }
}

void read_message_proc(int sock,char* message,int size)
{
    while(1)
    {
        if(read(sock,message,size) == 0)
            return;
        else
            printf("Message from server:%s\n",message);
    }

}



int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <IP> <port>\n",argv[0]);
        exit(1);
    }

    pid_t pid;
    char message[MAX_LEN];
    int sock;
    struct sockaddr_in sock_addr;

    memset(&sock_addr,0,sizeof(sock_addr));

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_port = htons(atoi(argv[2]));

    if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket() error");
        exit(1);
    }

    if(connect(sock,(const struct sockaddr*)&sock_addr,sizeof(sock_addr)) == -1)
    {
        perror("connect() error");
        exit(1);
    }

    if((pid = fork()) == 0)
        write_message_proc(sock,message,MAX_LEN);
    else
        read_message_proc(sock,message,MAX_LEN);

    close(sock);

    return 0;
}