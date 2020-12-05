#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
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
    else
    {
        printf("Socket successfully created\n");
    }
    

    // flushing the data in servaddr
    bzero(&servaddr, sizeof(servaddr));

    // giving input to struct sockaddr_in
    servaddr.sin_family = AF_INET;
    // htons() is host to network short
    servaddr.sin_port = htons(8000); // giving port no - 80 for httpserver
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
    else
    {
        printf("Connection established with the server");
    }
    
    
    

    return 0;
}