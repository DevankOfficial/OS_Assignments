#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read(char *file_n){ 
    FILE *fl;
    fl = fopen(file_n,"r");
    if (fl == NULL){return NULL;}
    fseek(fl, 0, SEEK_END);
    int len = ftell(fl);
    fseek(fl, 0, SEEK_SET);
    char *str = malloc(sizeof(char)*(len+1));
    char c;
    int i=0;
    while ((c=fgetc(fl)) != EOF){
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    fclose(fl);
    return str;
}

int main(int argc, char *argv[]){
    char *filename = argv[1];
    char *file_con = read(filename);
    if (file_con == NULL){
        printf("Error while reading.\n");
        return 1;}
    printf("File contents: \n%s\n", file_con);
    free(file_con);
    return 0;
}