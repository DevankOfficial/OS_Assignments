#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
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

int main()
{
    while (1){
    printf("Enter the command: ");
    char command[100];
    char operation[100];
    gets(command);gets(operation);
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
        pid_t pid = fork();
        if (pid == 0) {
            execl("./mkdir",operation, NULL);
        } else {
            wait(NULL);
        }
    }
    else if (strcmp(command,"rm")==0){
        pid_t pid = fork();
        if (pid == 0) {
            execl("./rm",operation, NULL);
        } else {
            wait(NULL);
        }
    }
    else if (strcmp(command,"date")==0){
        pid_t pid = fork();
        if (pid == 0) {
            execl("./date",NULL, NULL);
        } else {
            wait(NULL);
        }
    }
    else if (strcmp(command,"ls")==0){
        pid_t pid = fork();
        if (pid == 0) {
            execl("./ls",operation, NULL);
        } else {
            wait(NULL);
        }
    }
    else if (strcmp(command,"cat")==0){
        pid_t pid = fork();
        if (pid == 0) {
            execl("./cat",operation, NULL);
        } else {
            wait(NULL);
        }
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