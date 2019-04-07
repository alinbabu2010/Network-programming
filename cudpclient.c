#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main()
{
    int listenfd,port,r;
    char buff[1024],ip[20];
    struct sockaddr_in servaddr,cliaddr;
    socklen_t servlen;
    struct hostent *host;
    struct sockaddr_in serverAdd;
    printf("Enter the server ip address\n");
    scanf("%s",ip); 
    host = gethostbyname(ip);
    listenfd = socket(AF_INET,SOCK_DGRAM,0);
    if(listenfd==-1)
    {
        perror("Socket");
        return 0;
    }
    printf("Enter the port no: ");
    scanf("%d",&port);
    printf("The port no is %d",port);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr = *((struct in_addr *)host->h_addr);
    sendto(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
    r=recvfrom(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,&servlen);
    buff[r]=0;
    printf("\nThe time received from the server : %s\n",buff);
    exit(0);
    return 0;
}

