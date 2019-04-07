#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>
#define BUFOR 512
 
  
int main(int argc, char *argv[])  
 { 
 int fd, serverLength, cLength;
 
 struct sockaddr_in serverAddr, c_addr[2], clientAddr;  
 cLength = sizeof(clientAddr);
 char buf[BUFOR];  
 int clients = 0;
 int c_port[2];
 
 if(argc != 2)  
     {  
        printf(" portu");  
        exit(1);  
     } 
 
 uint16_t port = atoi( argv[ 1 ] ); 
 
 
 if ((fd = socket(AF_INET, SOCK_DGRAM, 0))==-1)
     {
        perror("Bad socket");
        exit(1); 
     }
 
 
 bzero((char*) &serverAddr, sizeof(serverAddr));  
 serverAddr.sin_family = AF_INET;  
 serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
 serverAddr.sin_port = htons(port);  
 serverLength = sizeof(serverAddr);
 
 
 
 if (bind(fd, (struct sockaddr* ) &serverAddr, serverLength)==-1)
     {
         perror("Blad bind");
         exit(1); 
     }
 
 
 for(;;)
    {
         printf("Receiving...\n");
 
         if (recvfrom(fd, buf, BUFOR, 0, (struct sockaddr*)&clientAddr, &cLength)==-1)  
             {
                  perror("Blad recvfrom");
                  exit(1); 
             }
 
         if (clients==0) 
 
            { 
                 c_addr[0] = clientAddr;
 
                 c_port[0] = ntohs(c_addr[0].sin_port);
 
                 clients++;
 
                 printf("Client 0 was connected. Port: %d\n",c_port[0]);
 
                 sendto(fd, "I am only one cleint.", 24, 0, (struct sockaddr*)&clientAddr, cLength);
            }else if(clients==1)
            {
 
                 if (c_port[0]==ntohs(clientAddr.sin_port))
                     {
 
                         sendto(fd, "I am only one client.", 24, 0, (struct sockaddr*)&c_addr[0], sizeof(c_addr[0]));
                         printf("One cleint\n");
                     }else
                     {
 
                          c_addr[1] = clientAddr;
                          c_port[1] = ntohs(c_addr[1].sin_port);
                          clients++;
                          printf("Second cleint\n");
                          sendto(fd, buf, BUFOR, 0, (struct sockaddr*)&c_addr[0], sizeof(c_addr[0]));
                      }
 
            }else
            {
 
 
               if (c_port[0]==ntohs(clientAddr.sin_port))
               {
 
                          printf("Sending emssage for client 1\n");
                          if (sendto(fd, buf, BUFOR, 0, (struct sockaddr*)&c_addr[1], sizeof(c_addr[0]))==-1)
                              {
                                   clients--;
                                   perror("Error senttoen");
                              }
               }else
               {
               
                          printf("Sending message for client 0\n");
                          if (sendto(fd, buf, BUFOR, 0, (struct sockaddr*)&c_addr[0], sizeof(c_addr[1]))==-1)
                              {
                                   clients--;
                                   perror("Blad senttoen");
                               }
                }
 
 
              }
 
 
 
      }
 
     close(fd);  
      return 0;
} 
