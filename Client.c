// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void dashboard();
void view();

int main(int argc, char const *argv[])
{
    int sockfd, n;
    char buffer[1024];
    struct sockaddr_in servaddr;

    //  Evaulating right number of argument
    if (argc != 2)
    {
        printf("usage: a.out <IPaddress>\n");
        exit(1);
    }

    //  checking the socket formation error
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        exit(1);
    }

    // flushing the data in servaddr
    bzero(&servaddr, sizeof(servaddr));

    // giving input to struct sockaddr_in
    servaddr.sin_family = AF_INET;
    // htons() is host to network short
    servaddr.sin_port = htons(9000); // giving port no - 80 for httpserver
    // now using inet_pton() ("presentation to numric") function to input in right format
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error\n");
        exit(1);
    }

    // connect function to connect with connect server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error\n");
        exit(1);
    }

    while (1)
    {

        dashboard();
        printf("       Enter your choice: ");
        char temporary[5];
        scanf("%[^\n]%*c", temporary);
        bzero(buffer, sizeof(buffer));
        strcpy(buffer, temporary);

        write(sockfd, buffer, sizeof(buffer));

        // now the time to select the game option
        if (strcmp(buffer, "1") == 0)
        {
            bzero(buffer, sizeof(buffer));
            read(sockfd, buffer, sizeof(buffer));
            view(buffer);
        }
        else if (strcmp(buffer, "2") == 0)
        {
        }
        else
        {
        }
        sleep(5);
    }

    return 0;
}

// Views of the game

void dashboard()
{
    system("clear");
    printf("\n\n\n");
    printf("%25c%s\n\n", ' ', "welcome to Tic-Tac-Toe Game");
    printf("%28c%s\n", ' ', "1. Create the Room");
    printf("%28c%s\n", ' ', "2. Join the Room");
    printf("%28c%s\n", ' ', "3. Exit the Game");
    printf("\n\n");
}


void view(char *num)
{
    system("clear");
    printf("\n\n\n\n");
    printf("%25c     |      |      \n", ' ');
    printf("%25c  %c  |   %c  |  %c   \n", ' ', num[0], num[1], num[2]);
    printf("%25c_____|______|______\n", ' ');
    printf("%25c     |      |      \n", ' ');
    printf("%25c  %c  |   %c  |  %c   \n", ' ', num[3], num[4], num[5]);
    printf("%25c_____|______|_____\n", ' ');
    printf("%25c     |      |      \n", ' ');
    printf("%25c  %c  |   %c  |  %c   \n", ' ', num[6], num[7], num[8]);
    printf("%25c     |      |      \n", ' ');
    printf("\n\n");
}


// Opting the to host 
