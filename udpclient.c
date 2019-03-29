// Client side implementation of UDP client-server model 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	int sock;
	struct sockaddr_in serverAdd;
	struct hostent *host;
	char sendMessage[512];
	host= (struct hostent *) gethostbyname((char *)"127.0.0.1");
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket Creation Failed");
		exit(1);
	}
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(5000);
	serverAdd.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(serverAdd.sin_zero),8);
	while (1)
	{
	     printf("Enter the Message:");
	     fgets(sendMessage,100,stdin);
	     sendto(sock, sendMessage, strlen(sendMessage), 0,(struct sockaddr   *)&serverAdd, sizeof(struct sockaddr));
	     memset (sendMessage , 0 , sizeof(sendMessage));
	} 
}
