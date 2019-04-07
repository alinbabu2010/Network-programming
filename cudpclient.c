#include <arpa/inet.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
 
#define BUFLEN 512    
 
 
int main(int argc, char *argv[])  
 {  
      struct sockaddr_in serv_addr;  
      int sockfd;
      socklen_t slen;
      slen=sizeof(serv_addr);  
      char buf[BUFLEN]; 
 
 if(argc != 3)  
   {  
       printf("Usage : %s <Server-IP>\n",argv[2]);  
       exit(0);  
   } 
 
 
 
 if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)  
   {
       perror("Socket Error");
       exit(1);
   }
 uint16_t port = atoi( argv[ 1 ] ); 
 
 bzero(&serv_addr, sizeof(serv_addr));  
 serv_addr.sin_family = AF_INET;  
 serv_addr.sin_port = htons(port);  
 serv_addr.sin_addr.s_addr = inet_addr(argv[2]);
 
 
 while(1)
   {
     bzero(buf,BUFLEN);
     printf("Attempting to READ to socket %d: ",sockfd);
     fflush(stdout);
 
     if(recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, &slen)==-1)  
        {
            perror("Blad bind");
            exit(1); 
        }
      printf("The message from the server is: %s \n",buf);
      printf("Please enter the message to send: ");
      bzero(buf,BUFLEN);
      fgets(buf,BUFLEN,stdin);
      printf("Attempting to write to socket %d: ",sockfd);
      fflush(stdout);
      
      if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
           {
               perror("Blad bind");
               exit(1); 
           }
 
   }
 
 
 close(sockfd);  
 return 0;
 
 
 
}
