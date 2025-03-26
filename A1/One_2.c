#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#define MAX 100

void echo(char* in){
    printf("%s\n",in);
}

void pwd(){
    char path[1024];
    getcwd(path,1024);
    printf("Current Working Directory: \n%s\n",path);
}

void cd(){
    char buff[1024];
    char* dir = ".";
    if (chdir(dir)==-1){
        printf("Directory change failed.\n");
        if (errno == ENOENT){
            printf("Path not Found.");
        }
    }
    else{
        printf("Directory Changed.\n");
    }
    pwd(buff);
}
void runner(char com,char oper,char follow){
    pthread_t t_id;
    if (strcmp(follow,"&t")!=0){
        return;
    }
    else{
        pthread_create(&t_id, NULL, com, oper);
        pthread_join(t_id, NULL);
    }
}

int main()
{
    //int pid = fork();
    while (1){
    printf("Enter the command: ");
    char command[MAX];
    char operation[MAX];
    char follow[MAX];
    gets(command);gets(operation);gets(follow);
    printf("%s",follow);
    printf("The Output is: \n");
    if (strcmp(command,"echo")==0)
    {
        echo(operation);
    }
    else if (strcmp(command,"cd")==0){
        cd();
    }
    else if (strcmp(command,"pwd")==0){
        pwd();
    }
    else if (strcmp(command,"mkdir")==0){
        runner("mkdir()",operation,follow);
    }
    else if (strcmp(command,"rm")==0){
        runner("rm()",operation,follow);
    }
    else if (strcmp(command,"date")==0){
        runner("date()",NULL,follow);
    }
    else if (strcmp(command,"ls")==0){
        runner("ls()",operation,follow);
    }
    else if (strcmp(command,"cat")==0){
        runner("cat()",operation,follow);
    }
    else if (strcmp(command,"exit")==0){
        printf("The application has ended.");
        break;
    }
    else{
        printf("Wrong Input.");
    }
    }
    return 0;
}