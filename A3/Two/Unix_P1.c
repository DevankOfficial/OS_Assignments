#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define LEN_P1_ARRAY 50
#define STRING_LEN 10
#define SENT_N 5
#define ALPHA 26
#define CLOCKS_PER_SEC  ((__clock_t) 1000000)
#define SOCKET_PATH__ "/tmp/arn"

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
    return res;
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

int main(){
    clock_t start, end;
    double execution_time;
    start = clock();

    struct sockaddr_un addr; 
    char* arr[LEN_P1_ARRAY]; arrcpy(GenerateRandomArray(), *arr, LEN_P1_ARRAY);
    char* sent_arr[SENT_N];
    int num;
    int sock_n;
    int* id_arr[SENT_N];

    sock_n=socket(AF_UNIX,SOCK_STREAM,0);
    memset(&addr,0,sizeof(struct sockaddr_un));
    addr.sun_family=AF_UNIX;
    strncpy(addr.sun_path,SOCKET_PATH__,sizeof(addr.sun_path)-1);
    if(connect(sock_n, (struct sockaddr *)&addr, sizeof(struct sockaddr_un))==-1){
        perror("Connection error");
    }

    for(int i=0;i<50;i++){
        int j=0;
        while(j<5){
            recv(sock_n, sent_arr, sizeof(char)*(SENT_N+1), 0);
            recv(sock_n, &id_arr , sizeof(int), 0);
            j++;
        }
        sleep(5);
        int temp=num;
        printf("%d\n",temp);
        send(sock_n, &temp, sizeof(int),0);
        i=temp;
        
    }
    close(sock_n);

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time Taken to execute: %f seconds\n", execution_time);
}