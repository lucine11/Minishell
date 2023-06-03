#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/wait.h"

int main()
{
    int pid;
    int fd[2];
    int fd1[2];
    char *var[] = {"/bin/ls","-l",NULL};
    char *var1[] = {"/usr/bin/wc","-l",NULL};
    char *var2[] = {"/usr/bin/wc","-l",NULL};

   pipe(fd);
   if(pipe(fd1)<0)
        printf("error\n");
    pid = fork();
    if(pid==0)
        {
            close(fd[0]);
            dup2(fd[1], 1);
            execve(var[0],var,NULL);
            exit(0);
        }else 
            wait(&pid);
        
        
        pid = fork();
    if(pid==0)
        {
             close(fd[1]);
            dup2(fd[0], 0);
             close(fd1[0]);
            dup2(fd1[1], 1);
            execve(var1[0],var1,NULL);
            exit(0);
        }else 
        {
            close(fd[0]);
            close(fd[1]);
            wait(&pid);
        }
         
pid = fork();
    if(pid==0)
        {
            printf("ok1\n");
            close(fd1[1]);
            dup2(fd1[0], 0);
            execve(var2[0],var2,NULL);
            exit(0);
        }else 
        {
             close(fd1[0]);
           close(fd1[1]);
            wait(&pid);
        }       
}

