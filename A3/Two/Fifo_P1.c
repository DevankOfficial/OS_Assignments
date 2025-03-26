#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <math.h>

#define LEN_P1_ARRAY 50
#define STRING_LEN 10
#define SENT_N 5
#define ALPHA 26
#define CLOCKS_PER_SEC  ((__clock_t) 1000000)

#define FIFO_PATH "/tmp/myfifo"

char* GenerateRandomString(){
    char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    char* res = "";
    for (int i = 0; i < STRING_LEN; i++){
        res = res + alphabet[rand() % ALPHA];
    }
    return res;
}

char* GenerateRandomArray(){
    char* res[LEN_P1_ARRAY];
    for (int i = 0; i < LEN_P1_ARRAY; i++){
        res[i] = GenerateRandomString();
    }
    return res[LEN_P1_ARRAY];
}

void arrcpy(char ar1[], char copy[], int n){
    for (int i=0;i<n;i++){
        memcpy((void *)copy[i], (void *)ar1[i], n);
    }
}
void arrcpy2(int ar1[], int copy[], int n){
    for (int i=0;i<n;i++){
        copy[i] = ar1[i];
    }
}

char* DivideArray(char* arr[], int start, int end){
    char* res[SENT_N];
    for (int i=start ;i<end ;i++){
        res[i-start] = arr[i];
    }
    return *res;
}

int* CreateIdArray(int start, int end){
    int* res[SENT_N];
    int arr[SENT_N];
    for (int i=start ;i<end ;i++){
        arr[i-start] = i;
    }
    arrcpy2(arr, *res, SENT_N);
    return *res;
}

int sendArr(char ar[], int fd, int curr_n, int n){
    for(int i=0;i<n;i++){
        if(write(fd, (const void*)ar[curr_n*5+i], sizeof(char)*STRING_LEN+1)==-1){
            perror("Some error writing");
        }
    }
}
int sendArr2(int ar[], int fd, int curr_n, int n){
    for(int i=0;i<n;i++){
        if(write(fd, (const void*)ar[curr_n*5+i], sizeof(char)*STRING_LEN+1)==-1){
            perror("Some error writing");
        }
    }  
}

int intlen(int n){
    return floor(log10(abs(n))) + 1;
}

int main(){
    clock_t start, end;
    double execution_time;
    start = clock();
    int fifoD;

    char* arr[LEN_P1_ARRAY]; arrcpy(GenerateRandomArray(), *arr, LEN_P1_ARRAY);
    char* sent_arr[SENT_N];
    int j=0;
    int num;
    int* id_arr[SENT_N];
    char * myfifo = "myfifo";

    mkfifo(myfifo, 0666);
    
    for (int i=0;i<LEN_P1_ARRAY;i++){
        // Open FIFO for write only
        if (fifoD=open(myfifo, O_WRONLY)){
            perror("Error Occured while Opening Fifo");
        }
        
        memcpy(DivideArray(arr, i, i+4), *sent_arr, sizeof(sent_arr));
        memcpy(CreateIdArray(i, i+4), *id_arr, sizeof(id_arr));
        char *temp=malloc(sizeof(char)*21);
        for(int j=0;j<SENT_N;j++){
            temp=arr[i]; 
            if(write(fifoD,sent_arr[j],sizeof(char)*(STRING_LEN+1))==-1){
                perror("Some error writing");
            }
        }  
        // sendArr((char*)sent_arr, fifoD, i, SENT_N);
        // sendArr2((int*)id_arr, fifoD, i, SENT_N);
        close(fifoD);

        if (fifoD = open(myfifo, O_RDONLY)==-1){
            perror("Fifo File could not be Opened for reading.");
        }
        read(fifoD, (void*)(intptr_t)num, intlen(num)+1);
        char *read_int=malloc(sizeof(char)*STRING_LEN+1);
        if(read(fifoD, read_int, sizeof(int) *STRING_LEN+1)==-1){
            perror("Some error reading");
        }
        i = read_int;
        printf("Max Id Recieved: %d", i);
        close(fifoD);
    }

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time Taken to execute: %f seconds\n", execution_time);
    return 0;
}