#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 2000
#define CLADDR_LEN 100
int main()
{
	int  len,ret, newsock,sock;
	char buffer[BUF_SIZE];
	pid_t childpid;
	char clientAddr[CLADDR_LEN];       
	struct sockaddr_in serverAdd, clientAdd;   
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)  //Socket creation and checking
	{
		perror("Socket creation is failed");
		exit(1);
	}
	serverAdd.sin_family = AF_INET;        
	serverAdd.sin_port = htons(5000);
	serverAdd.sin_addr.s_addr = INADDR_ANY;
	bzero(&(serverAdd.sin_zero),8);
	if (bind(sock, (struct sockaddr *)&serverAdd, sizeof(struct sockaddr))== -1)  //Binding socket
	{
		perror("Unable to bind");
		exit(1);
	}
	if (listen(sock, 3) == -1)  //Listening for connection
	{
		perror("Listen");
		exit(1);
	}
	printf("TCPServer Waiting for client connection\n");
	fflush(stdout);
	while(1)
	{																											        
			len = sizeof(clientAdd);
		  	newsock = accept(sock, (struct sockaddr *) &clientAdd, &len);  //Aceepting and checking connection
		    	if (newsock < 0) 
			{
			       printf("Error accepting connection!\n");
			       exit(1);
			}
		     	printf("Connection accepted...\n");
			inet_ntop(AF_INET, &(clientAdd.sin_addr), clientAddr, CLADDR_LEN);
		  	if ((childpid = fork()) == 0) 
			{ 
				//creating a child process
				close(sock); 	    
			        while(1) 
				{
			            memset(buffer, 0, BUF_SIZE);
			            ret = recvfrom(newsock, buffer, BUF_SIZE, 0, (struct sockaddr *) &clientAdd, &len); //Receiving message
			            if(ret < 0) 
				    {
			                 printf("Error receiving data!\n");  
			                 exit(1);
			            }
			            printf("Received data from %s: %s\n", clientAddr, buffer); 
			            ret = sendto(newsock, buffer, BUF_SIZE, 0, (struct sockaddr *) &clientAdd, len);  //Sending message   
			            if (ret < 0) 
				    {  
			                 printf("Error sending data!\n");  
			                 exit(1);  
			            }  
			            printf("Sent data to %s: %s\n", clientAddr, buffer);
			       }
			}
			close(newsock);
	}
	return 0;
}
