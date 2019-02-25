#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
struct msgbuff
{
	long msgtype;
	char msgs[400];
}s1,s2,s3,s4;
int k,mid;
int main()
{
	mid=msgget(25,IPC_CREAT|0666);
	printf("Enter the string\n");
	scanf("%[^\n]s",s1.msgs);
	printf("Enter the key\n");
	scanf("%s",s2.msgs);
	s1.msgtype=1;
	k=msgsnd(mid,&s1,400,0);
	s2.msgtype=1;
	k=msgsnd(mid,&s2,400,0);
	k=msgrcv(mid,&s3,400,2,0);
	k=msgrcv(mid,&s4,400,2,0);
	printf("Encoded String : %s\n",s4.msgs);
	printf("Key : %s\n",s3.msgs);
	return 0;
}
