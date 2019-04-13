#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
	char buf[100],domain[20],snd[25];
	int k,i=0,j,m=0;
	socklen_t len;
	int sock_desc;
	struct sockaddr_in client,server;
	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));
	sock_desc = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_desc == -1)
	{
		printf("\nError in socket creation\n");
		exit(1);
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3500;
	k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	if(k==-1)
	{
		printf("Error in binding\n");
		exit(1);
	}
	len=sizeof(server);
	k=recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr*)&server,&len);
	if(k==-1)
	{
		printf("Error in receiving\n");
		exit(1);
	}
	strcpy(snd,buf);
	while(i<(strlen(buf)))
	{
		if(buf[i]=='@')
		{
			for(j=i+1;j<strlen(buf);j++)
				domain[m++]=buf[j];
			break;
		}
		i++;
	}
	printf("Receiving mail.....\n");
	printf("Domain verifed << %s >>\n",domain);
	len=sizeof(server);
	k=recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr*)&server,&len);
	if(k==-1)
	{
		printf("\nError in receiving\n");
		exit(1);
	}
	printf("From  : %s\n",buf);
	len=sizeof(server);
	k=recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr*)&server,&len);
	if(k==-1)
	{
		printf("\nError in receiving\n");
		exit(1);
	}
	printf("Subject : %s\n",buf);
	printf("Message : ");
	len=sizeof(server);
	k=recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr*)&server,&len);
	if(k==-1)
	{
		printf("\nError in receiving\n");
		exit(1);
	}
	while(strcmp(buf,".")!=0)
	{
		printf("%s\n\t",buf);
		len=sizeof(server);
        	k=recvfrom(sock_desc,buf,sizeof(buf),0,(struct sockaddr*)&server,&len);
        	if(k==-1)
        	{
                	printf("\nError in receiving\n");
                	exit(1);
        	}
	}
	printf("Mail recieved sucessfully from %s\n",snd);	
	close(sock_desc);
	return 0;
}
