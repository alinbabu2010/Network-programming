#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct msgbuff
{
	long msgtype;
	char msgs[400];
}s1,s2,s3,s4;
int k,mid,i;
char str[400],str1[400];
int main()
{
	mid=msgget(25,IPC_CREAT|0666);
	k=msgrcv(mid,&s1,400,1,0);
	strcpy(str,s1.msgs);
	for(i=0;i<strlen(str);i++)
        {
             //Encoding string
             if(str[i]=='y')
                   str[i]='a';
             else if(str[i]=='Y')
                   str[i]='A';
             else if(str[i]=='z')
                   str[i]='b';
             else if(str[i]=='Z')
                   str[i]='B';
	     else if(str[i]==' ')
                   str[i]=' ';
             else
                   str[i]=str[i]+2;
	}
	k=msgrcv(mid,&s2,400,1,0);
	s3.msgtype=2;
	s4.msgtype=2;
	strcpy(str1,s2.msgs);
	for(i=0;i<strlen(str1);i++)
        {
		if(isdigit(str1[i]))
			str1[i]+=1;
		
	}
	strcpy(s4.msgs,str1);
        k=msgsnd(mid,&s4,400,0);
	strcpy(s3.msgs,str);
	k=msgsnd(mid,&s3,400,0);
	return 0;
}
