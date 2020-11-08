// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int sockfd, n;
  char buffer[1024];
  struct sockaddr_in servaddr;

  //  Evaulating right number of argument
  if(argc != 2){
    printf("usage: a.out <IPaddress>\n");
    exit(1);
  }

  //  checking the socket formation error
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("socket error\n");
    exit(1);
  }

  // flushing the data in servaddr
  bzero(&servaddr, sizeof(servaddr));

  // giving input to struct sockaddr_in
  servaddr.sin_family = AF_INET;
  // htons() is host to network short
  servaddr.sin_port = htons(8080); // giving port no - 80 for httpserver
  // now using inet_pton() ("presentation to numric") function to input in right format
  if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
    printf("inet_pton error\n");
    exit(1);
  }

  // connect function to connect with connect server
  if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
    printf("connect error\n");
    exit(1);
  }

  while(1){
    bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s\n", buffer);

    char temporary[5];
    scanf("%[^\n]%*c", temporary);
    bzero(buffer, sizeof(buffer));
    strcpy(buffer, temporary);

    write(sockfd, buffer, sizeof(buffer));

    bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s\n", buffer);

  }


	return 0;
}
