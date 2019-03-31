//Muliti user chat using TCP : Server
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
#include <arpa/inet.h>
#define CLADDR_LEN 100
void error(char *msg)     //Function to display error messages
{
      perror(msg);
      exit(1);
}
int main(int argc, char *argv[])
{
          int sockfd, newsockfd, portno, clilen, k;
          char buffer[256];
          pid_t childpid;
          struct sockaddr_in serv_addr, cli_addr;
          int n;
          char clientAddr[CLADDR_LEN];
          //Checking whether port number is given
          if (argc < 2)
          {
            fprintf(stderr, "Error,no port provided\n");
            exit(1);
          }
          //Socket creation
          sockfd = socket(AF_INET, SOCK_STREAM, 0);
          if (sockfd < 0)
          {
            error("Error opening socket");
          }
          bzero((char *)&serv_addr, sizeof(serv_addr));
          portno = atoi(argv[1]);
          //Setting sockets
          serv_addr.sin_family = AF_INET;
          serv_addr.sin_addr.s_addr = INADDR_ANY;
          serv_addr.sin_port = htons(portno);
          //Binding socket
          if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
          {
            error("Error on binding");
          }
          //Listening from specified port
          k = listen(sockfd, 5);
          for (;;)
          {
            clilen = sizeof(cli_addr);
            if (k < 0)
            {
              error("Error on inding the network");
              exit(1);
            }
            printf("Server is running...........................\n         Waiting for the client on the port number: %d\n", portno);
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);   //Accepting and checking connection
            if (newsockfd < 0)
            {
              error("Error on accept");
            }
            printf("Connection accepted...\n");
            inet_ntop(AF_INET, &(cli_addr.sin_addr), clientAddr, CLADDR_LEN);
            if ((childpid = fork()) == 0)
            { //creating a child process
              close(sockfd);
              //stop listening for new connections by the main process.
              //the child will continue to listen.
              //the main process now handles the connected client.
              for (;;)
              {
                bzero(buffer, 256);
                n = read(newsockfd, buffer, 255);   //Reading from buffer
                if (n < 0)
                {
                  error("Error reading from socket");
                }
                else
                {
                  printf("Client at %s: %s\n", clientAddr, buffer);
                }
                bzero(buffer, 256);
                printf("Enter your message: %s", buffer);
                fgets(buffer, 256, stdin);
                n = write(newsockfd, buffer, strlen(buffer));  //Writing into buffer
                if (n < 0)
                {
                  error("Error writing socket");
                }
              }
            }
            close(newsockfd);
          }
}
