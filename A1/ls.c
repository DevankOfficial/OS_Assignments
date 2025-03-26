#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

long int getSize(char file[]){
    FILE *fp = fopen(file, "r");
    if (fp == NULL){printf("File not found."); return -1;}
    fseek(fp, 0L, SEEK_END);
    long int res = ftell(fp);
    fclose(fp);
    return res;
}
void Eq(char l[0], char arr[]){
     int size = sizeof(arr)/sizeof(arr[0]);
    for (int i=0;i<size;i++){
        l[i]=arr[i];
    }
}

int main(int argc, char *argv[]){
    DIR *dr; 
    struct dirent *de;
    dr = opendir(".");
    char* cond = argv[1];
    char name[0]; Eq(name, de->d_name);
    unsigned char type = de->d_type;
    printf("%s %s",name,type);
    //execl(argv[0],argv);
    if (!dr){
        printf("Cound Not Open Directory.\n");
        return 1;
    }
    if (strcmp(cond,"-s")==0){
        while ((de = readdir(dr)) != NULL){
            int size = getSize(name);
            printf("%d %s\n",size, name);
        }
    }
    else{
    while ((de = readdir(dr)) != NULL){
        if (type == DT_REG)
        {
            printf("File: %s\n", name);}
        else if (type == DT_DIR){
            printf("Dir: %s\n", name);}
        else{
            printf("%s", name);
        }
    }
    }
    if (closedir(dr) == -1){
        printf("Error Closing Directory.\n"); return 1;
    }
    return 0;
}