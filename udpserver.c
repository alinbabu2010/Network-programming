// Serveside implementation of UDP client-server model 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
 
int main()
{
        int sock;
        int IPlength, TotalByte;
        char message[512];
        struct sockaddr_in serverAdd , clientAdd;
        if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
            perror("Socket Creation Failed");
            exit(1);
        }
        serverAdd.sin_family = AF_INET;
        serverAdd.sin_port = htons(5000);
        serverAdd.sin_addr.s_addr = INADDR_ANY;
        bzero(&(serverAdd.sin_zero),8);
        if (bind(sock,(struct sockaddr *)&serverAdd,sizeof(struct sockaddr)) == -1)
        {
            perror("Bind Error");
            exit(1);
        }
        IPlength = sizeof(struct sockaddr);
        printf("\nUDP Server Waiting for client Message\n");
        fflush(stdout);
        while (1)
        {
		TotalByte = recvfrom(sock,message,512,0,(struct sockaddr *)&clientAdd, &IPlength);
		message[TotalByte] = '\0';
            	printf("Received Message: %s", message);
		fflush(stdout);
        }
        return 0;
}
