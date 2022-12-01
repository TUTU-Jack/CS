#include <stdio.h>
#include "file.h"
#include <string.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("Usage %s <command>\n",argv[0]);
        exit(1);
    }

    if(strcmp(argv[1],"cp") == 0)
    {
        cp1(argv[2],argv[3]);
        cp(argv[2],argv[3]);
    }
    else if(strcmp(argv[1],"ls") == 0)
        ls(argv[2],argv[3]);

    return 0;
}