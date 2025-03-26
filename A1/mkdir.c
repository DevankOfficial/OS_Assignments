#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    int check;
    check = mkdir(argv[1]);
    if (check == -1){
        printf("Directory Creation Failed.\n");
    }
    else{
        printf("Directory Created Succesfully.\n");
    }
}