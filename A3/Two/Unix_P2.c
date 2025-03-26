#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define LEN_P1_ARRAY 50
#define STRING_LEN 10
#define RECIEVE_N__ 5
#define SOCKET_PATH__ "/tmp/arn"
#define CLOCKS_PER_SEC  ((__clock_t) 1000000)

int main() {
    clock_t start, end;
    double execution_time;
    start = clock();
    char* recieve[RECIEVE_N__];
    int Id_arr_r[RECIEVE_N__];
    int conf_flag = 0;
    int max_id_recieved;

    sleep(1);
    struct sockaddr_un addr;
    ssize_t numRead;
    int sock_d,acc_pt;
    if(remove(SOCKET_PATH__)==-1 && errno!=ENOENT){
        perror("Socket removed");
    }
    if ((sock_d=socket(AF_UNIX,SOCK_STREAM,0))==-1){
        perror("Socket cant be created");
    }
    memset(&addr,0,sizeof(struct sockaddr_un));
    addr.sun_family=AF_UNIX;
    strncpy(addr.sun_path,SOCKET_PATH__,sizeof(struct sockaddr_un)-1);
    bind(sock_d,(struct sockaddr *)&addr,sizeof(struct sockaddr_un));
    listen(sock_d,2);
    acc_pt=accept(sock_d,NULL,NULL);

    for(int i=0;i<LEN_P1_ARRAY;i++){
        int j=0;
        while(j<RECIEVE_N__){
            int x=i+j;
            send(acc_pt,recieve[x],sizeof(char)*(STRING_LEN+1),0);
            send(acc_pt,&Id_arr_r[x],sizeof(int),0); 
            j++;
        }
        sleep(1);
        int *k=malloc(sizeof(int));
        recv(acc_pt, k, sizeof(int),0);
        printf("%d\n",*k);
        i=(*k);
    }
    close(acc_pt);
    close(sock_d);

    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Time Taken to execute: %f seconds\n", execution_time);
    return 0;
}