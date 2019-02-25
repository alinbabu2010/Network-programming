#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define size 100
int main()
{
        char str[20];
        char *shmaddr,*e;
        key_t key;
        int i,shmid,num,result;
        key=2574095;
        shmid=shmget(key,size,IPC_CREAT|0666);
        if(shmid<0)
        {
           printf("Error occured in shmid\n");
           exit(1);
        }
        shmaddr=shmat(shmid,NULL,0);
        if(shmaddr==(char*)-1)
        {
           printf("Error occured in shmaddr\n");
           exit(1);
        }
        sscanf(shmaddr,"%s",str);
	result=0;
	e=str;
        while(*e!='\0')
        {
          if(isdigit(*e))
          {  num=atoi(e);
	     result+=num;
	  }
	  e++;
        }
        printf("Result : %d\n",result);
        return 0;
}

