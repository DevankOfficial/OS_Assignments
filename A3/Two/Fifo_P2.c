#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define LEN_P1_ARRAY 50
#define STRING_LEN 10
#define RECIEVE_N__ 5
#define CLOCKS_PER_SEC  ((__clock_t) 1000000)

int intlen(int n){
    return floor(log10(abs(n))) + 1;
}

void arrcpy(char ar1[], char copy[], int n){
    for (int i=0;i<n;i++){
        memcpy((void *)copy[i], (const void * restrict)ar1[i], n);
    }
}
void arrcpy2(int ar1[], int copy[], int n){
    for (int i=0;i<n;i++){
        copy[i] = ar1[i];
    }
}

int GetMaxId(int arr[],int n){
    int max=arr[0];
    for (int i=0;i<n;i++){
        if (max<arr[i]){max = arr[i];}
    }
    return max;
}

void Display(int ids, char arr){
    printf("Index %d : Element %s\n", ids, arr);
}

int main(){
    clock_t start, end;
    double execution_time;
    start = clock();

    int fifoRead;
    int fifoWrite;

    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);

    char recieve[RECIEVE_N__];
    int Id_arr_r[RECIEVE_N__];
    for (int i=0;i<LEN_P1_ARRAY;i++){
        // First open in read only and read
        if (fifoRead = open(myfifo,O_RDONLY)==-1){
            perror("File not Opened.");
        }
        
        char *temp=malloc(sizeof(char)*STRING_LEN+1);
        for(int j=0;j<RECIEVE_N__;j++){
            char *string = malloc(sizeof(char)*STRING_LEN+1);
            if(read(fifoRead, (void*)string, sizeof(char) *STRING_LEN+1)==-1){
                perror("Some error reading on recieve array");
            }
            printf("Index %d : Element %s\n", i, string);
            if (j == RECIEVE_N__-1){
                temp = j;
            }
        }
        close(fifoRead);

        fifoWrite = open(myfifo,O_WRONLY);
        if(write(fifoWrite, (const void *)temp, sizeof(char)*11)==-1){
                perror("Some error writing");
        }
        close(fifoWrite);
    }

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time Taken to execute: %f seconds\n", execution_time);
    return 0;
}