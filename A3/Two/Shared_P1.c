#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <math.h>
#include <stdint.h>        //giving seg fault

#define LEN_P1_ARRAY 50
#define STRING_LEN 10
#define SENT_N 5
#define ALPHA 26
#define SHARE_SIZE 1024
#define CLOCKS_PER_SEC  ((__clock_t) 1000000)

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
        copy[i] = ar1[i];
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
    char* arr[LEN_P1_ARRAY]; arrcpy(GenerateRandomArray(), *arr, LEN_P1_ARRAY);
    char* sent_arr[SENT_N];
    void* shared;
    int j=0;
    int num;
    int* id_arr[SENT_N];
    
    key_t key = ftok("aaaaa", 1);
    int shmid = shmget(key, sizeof(shared), IPC_CREAT | 0777);
    if (shmid == -1) {
        perror("Could not get shared memory");
        return EXIT_FAILURE;
    }
    const char* name = "shared_mem";
    int fd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    struct stat sb;
    fstat(fd, &sb);

    void* ptr;
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SHARE_SIZE);
    ptr = mmap(0, SHARE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    while (1){
        memcpy(DivideArray(arr, j, j+4), *sent_arr, sizeof(sent_arr));
        memcpy(CreateIdArray(j, j+4), *id_arr, sizeof(id_arr));
    
        sprintf(ptr, "%p", sent_arr);
        ptr += SENT_N+1;
        sprintf(ptr, "%p", id_arr);
        ptr += SENT_N+1;

        num = (intptr_t)ptr;
        j = num;
        if (j == LEN_P1_ARRAY){
            break;
        }
    }

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time Taken to execute: %f seconds\n", execution_time);
    return 0;
}