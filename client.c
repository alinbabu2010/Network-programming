#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define size 1024
int main()
{
        char str[20];
        char *shmaddr;
        key_t key;
        int shmid;
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
        printf("Enter the string\n");
        scanf("%s",str);
        sprintf(shmaddr,"%s",str);
        return 0;
}















