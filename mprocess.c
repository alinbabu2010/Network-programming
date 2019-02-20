//Creation of two child process//
//Done by:Alin Babu,7,R6//
#include<stdio.h>
#include<sys/types.h>
int pid1,pid2;
pid_t fork(void);
pid_t getpid(void);
pid_t getppid(void);
int i,j,k,ch,n,m,p,q;
int A[20][20],B[20][20],C[20][20];
void mataddition()
{
        if(n==p && m==q)
        {
                printf("Sum of matrices :\n");
                for(i=0;i<n;i++)
                {
                        for(j=0;j<m;j++)
                        {
                                C[i][j]=A[i][j]+B[i][j];
                                printf("%d\t",C[i][j]);
                        }
                        printf("\n");
                }
        }
        else
                printf("Number of rows and column are not equal\n");
}
void matpro()
{
        if(n==q && p==m)
        {
                for(i=0;i<n;i++)
                {
                        for(j=0;j<p;j++)
                        {
                                C[i][j]=0;
                                for(k=0;k<q;k++)
                                        C[i][j]+=(A[i][k]*B[k][j]);
                        }
                }
                printf("Product of matrices :\n");
                for(i=0;i<n;i++)
                {
                        for(j=0;j<q;j++)
                                printf("%d\t",C[i][j]);
                        printf("\n");
                }
        }
        else
                printf("Multiplication not possible\n");
}
int main()
{
        printf("Enter the rows and column of first matrix\n");
        scanf("%d%d",&n,&m);
        printf("Enter the first matrix\n");
        for(i=0;i<n;i++)
                for(j=0;j<m;j++)
                        scanf("%d",&A[i][j]);
        printf("Enter the rows and column of second matrix\n");
        scanf("%d%d",&p,&q);
        printf("Enter the second matrix\n");
        for(i=0;i<p;i++)
                for(j=0;j<q;j++)
                        scanf("%d",&B[i][j]);
        printf("Parent Process  of child 1|| Pid : %d\n",getpid());
        pid1=fork();
        if(pid1==-1)
                printf("Error occured\n");
        else if(pid1==0)
        {
		printf("Child Process 1 || Pid : %d\n",getpid());
		printf("Parent Process  of child 1|| Pid : %d\n",getppid());
                mataddition();
        }
        else if(pid1>0)
        {
                pid2=fork();
                if(pid2==-1)
                        printf("Error occured\n");
                else if(pid2==0)
                {
			printf("Child Process 2 || Pid : %d\n",getpid());
			printf("Parent Process  of child 1|| Pid : %d\n",getppid());
                        matpro();
                }

        }
        return 0;
}
