//Muliti user chat using TCP : Client
//Author : Alin Babu
//Class : R6
//Roll No : 67
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
void error(char *msg)     //Function to display error messages
{
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[])
{
    int sockfd, portno, n, newsockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    //Checking whether port number and IP address is given
    if (argc < 3)
    {
        fprintf(stderr, "Use %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    //Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error opening socket");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Error,no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    //Setting sockets
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    //Connecting to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Error connecting\n");
    }
    bzero(buffer, 256);
    printf("Enter your message: %s ", buffer);
    while (fgets(buffer, 256, stdin) != NULL)
    {
        n = write(sockfd, buffer, strlen(buffer)); //Writing into buffer
        if (n < 0)
        {
            error("Error writing to socket");
        }
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);    //Reading from buffer
        if (n < 0)
        {
            error("Error reading rom socket");
        }
        else
        {
            printf("Server: ");
            fputs(buffer, stdout);
	        bzero(buffer, 256);  //Clearing buffer
            printf("\n");
	        printf("Enter your message: %s ", buffer);
        }
    }
    return 0;
}
