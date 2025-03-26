#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    int check;
    char* file_name = argv[1];
    check = remove(file_name);
    if (check != 0){
        printf("File Removal Failed.\n");
        switch (errno)
        {
        case ENOENT:
            printf("Path not found.\n");
        case ENOTEMPTY:
            printf("File not empty.\n");
        case EACCES:
            printf("An open handle to the file exists.\n");
        }
        return 1;
    }
    else{ 
        printf("File Removed Successfully.\n");
    }
    return 0;
}