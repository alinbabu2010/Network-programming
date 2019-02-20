#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<ctype.h>
pid_t pid;
int p,i;
char str[20];
int main(){
	int fd[2];
	printf("Enter the string \n");
	scanf("%[^\n]s ",str);
	p=pipe(fd);
	if(p==-1){
		printf("Error occured \n");
	}
	else{
		printf("Sucessfully created the pipe \n");
	}
	pid=fork();
	if(pid<0){
		printf("Error occured \n");
	}
	else if(pid==0){
		read(fd[0],str,strlen(str));
		for(i=0;i<strlen(str);i++){
			if(str[i]=='y')
				str[i]='a';
			else if(str[i]=='Y')
                                str[i]='A';
			else if(str[i]=='z')
                                str[i]='b';
			else if(str[i]=='Z')
                                str[i]='B';
			else if(isspace(str[i]))
                                str[i]=' ';
			else
				str[i]+=2;
		}
		printf("Encoded string : %s",str);
	}
	else if(pid>0){
		write(fd[1],str,strlen(str));
	}
        return 0;
}
