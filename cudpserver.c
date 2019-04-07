#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
int main()
{
	int sfd,r,bi,port;
	char buff[1024];
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1)
	{
		perror("Socket");
		return 0;
	}
	printf("\n Enter the port no: ");
	scanf("%d",&port);
	printf("The port no is %d\n",port);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	bi=bind(sfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(bi==-1)
	{
		perror("Bind()");
		return 0;
	}
	while(1)
	{
		clilen = sizeof(cliaddr);
		r=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,&clilen);
		buff[r]=0;
		time_t ticks;
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%24s\r\n",ctime(&ticks));
		sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	}
	return 0;
}