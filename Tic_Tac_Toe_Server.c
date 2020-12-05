/**
 * Team Project
 * 
 * Team Members:
 * 1) Aditya Raj
 * 2) Tanmay 
 * 3) Nisarg
*/

/**
 * Project Content
 * 1) TCP server Implemented
 * 2)
 * 3)
 * 
*/


// Module needed
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

/**
 * Function Declaration
*/



/* Driver Function */
int main(int argc, char *argv[])
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;

    // socket formation and error checking
    if((sockfd= socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Error: Socket creation failed...");
        exit(1);
    }else{
        printf("Socket successfully created...\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    
    // passing data to structure sockaddr_in
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8000);


    // Binding the created socket to the IP address
    if((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1){
        printf("Error: Socket bind failed...\n");
        exit(1);
    }else{
        printf("Socket successfully binded...\n");
    }


    // Calling listen call to put server in listen state
    if((listen(sockfd, 10)) != 0){
        printf("Error: Listen failed...\n");
        exit(1);
    }{
        printf("Server listening...\n");
    }

    ////////////////////////////////////////////////////
    /// Accepting the client request
    int len = sizeof(cliaddr);
    if(connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len) < 0){
        printf("Error: Server accept failed...\n");
        exit(1);
    }else{
        printf("Server accepted the client");
    }

    ///////////
    
    
   
    close(sockfd);

    return 0;
}

