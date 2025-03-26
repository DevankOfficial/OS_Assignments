#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <math.h>
#include <stdint.h>        //giving seg fault

#define LEN_P1_ARRAY 50
#define STRING_LEN 10
#define RECIEVE_N__ 5
#define SHARE_SIZE 1024
#define CLOCKS_PER_SEC  ((__clock_t) 1000000)

int intlen(int n){
    return floor(log10(abs(n))) + 1;
}

int GetMaxId(int arr[],int n){
    int max=arr[0];
    for (int i=0;i<n;i++){
        if (max<arr[i]){max = arr[i];}
    }
    return max;
}

void Display(int ids[],char* arr[]){
    for (int i=0;i<RECIEVE_N__;i++){
        printf("Index %d : %s\n",ids[i],arr[i]);
    }
}

void arrcpy(char ar1[], char copy[], int n){
    for (int i=0;i<n;i++){
        copy[i] = ar1[i];
    }
}
void arrcpy2(int ar1[], int copy[], int n){
    for (int i=0;i<n;i++){
        copy[i] = ar1[i];
    }
}

int main(){
    clock_t start, end;
    double execution_time;
    start = clock();
    char* recieve[RECIEVE_N__];
    int Id_arr_r[RECIEVE_N__];
    int conf_flag = 0;
    int max_id_recieved;

    sleep(2);
    const char* name = "shared_mem";
    int fd;
    void* ptr;
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SHARE_SIZE);
    ptr = mmap(0, SHARE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    while(1){
        memcpy(ptr, (char*)recieve, sizeof(recieve));
        memcpy(ptr, (int*)Id_arr_r, sizeof(Id_arr_r));
        Display(Id_arr_r, recieve);

        max_id_recieved = GetMaxId(Id_arr_r, RECIEVE_N__);
        sprintf(ptr, "%d", max_id_recieved);
        ptr += intlen(max_id_recieved);

        if (max_id_recieved == LEN_P1_ARRAY){
            break;
        }
    }

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time Taken to execute: %f seconds\n", execution_time);
    return 0;
}