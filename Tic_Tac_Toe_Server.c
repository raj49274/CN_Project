// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

// function declaration
void hostTheGame();
void getDate();

int main(int argc, char const *argv[])
{
    int listenfd, connfd;
    char buffer[1024];
    struct sockaddr_in servaddr;
    time_t ticks;

    // creating listening Socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        exit(1);
    }

    //flusing the value os servaddr
    bzero(&servaddr, sizeof(servaddr));

    // giving input to struct sockaddr_in
    servaddr.sin_family = AF_INET;
    //
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // htons() is host to network short
    servaddr.sin_port = htons(9000); // giving port no - 80 for httpserver

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind error\n");
        exit(1);
    }

    //starting listening on created Socket
    if (listen(listenfd, 5) < 0)
    {
        printf("listen error\n");
        exit(1);
    }

    // creating new socket to accept the connection
    for (;;)
    {
        if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0)
        {
            printf("connection error\n");
            exit(1);
        }
        while (1)
        {

            bzero(buffer, sizeof(buffer));
            read(connfd, buffer, sizeof(buffer));

            if (strcmp(buffer, "1") == 0)
            {
                printf("1 is received\n");
                hostTheGame(connfd);
            }
            else if (strcmp(buffer, "2") == 0)
            {
                printf("2 is received\n");
                getDate(connfd);
            }
            else if (strcmp(buffer, "3") == 0)
            {
                printf("3 is received\n");
                write(connfd, buffer, sizeof(buffer));
                exit(0);
            }
            else
            {
                close(connfd);
            }
        }
    }
}

// function to process the incoming request
void hostTheGame(int socket)
{
    char Buffer[256];
    char temp[20];
    bzero(Buffer, sizeof(Buffer));
    strcpy(Buffer, "123456789");
    write(socket, Buffer, sizeof(Buffer));
}

// function to show date
void getDate(int socket)
{
    time_t t;
    time(&t);
    char Buffer[256];
    char result[50];
    char temp[20];
    bzero(result, sizeof(result));
    struct tm dt = *localtime(&t);

    sprintf(temp, "%d/", dt.tm_mday);
    strcat(result, temp);
    sprintf(temp, "%d/", dt.tm_mon + 1);
    strcat(result, temp);
    sprintf(temp, "%d", dt.tm_year + 1900);
    strcat(result, temp);

    bzero(Buffer, sizeof(Buffer));
    strcpy(Buffer, result);
    write(socket, Buffer, sizeof(Buffer));
}