#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
int pid,p1,p2,i;
char str1[50],str2[50];
int main(){
	int fd1[2],fd2[2];
	p1=pipe(fd1);
	if(p1==-1)
		printf("error\n");
	else
		printf("sucess");
	p2=pipe(fd2);
	if(p2==-1)
                printf("error\n");
        else
                printf("sucess");
	printf("Enter the first string\n");
	scanf("%s['\n']",str1);
	printf("Enter the second string\n");
        scanf("%s['\n']",str2);
	pid=fork();
	if(pid==-1)
		printf("Error\n");
	else if(pid==0){
		printf("writing string to pipe1 ");
		write(fd1[1],str1,strlen(str1));
		printf("reading string from pipe2 ");
                read(fd2[1],str2,strlen(str2));
		strcat(str1,str2);
		printf("Concatenated string : %s",str1);
	}
	else if(pid>0){
		printf("writing string to pipe2 ");
                write(fd2[0],str2,strlen(str2));
                printf("reading string from pipe1 ");
                read(fd1[0],str1,strlen(str1));
                strcat(str2,str1);
                printf("Concatenated string : %s",str2);
        }
	return 0;
}
