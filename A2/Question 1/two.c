#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <math.h>
#define BILLION 1000000000L
#define NO_OF_PROCESSES 3

void linux_compiler(){
    execl("make", "-j8", NULL);
    execl("sudo make modules_install", "-j8", NULL);
    execl("sudo make install", "-j8", NULL);
    exit(0);
}

double* countA(){
    struct timespec start, stop;
    double accum;

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    printf("Process A has started.\n");
    pid_t pid = fork();
    if (pid == 0){
        linux_compiler();
    }
    else{
        wait(NULL);
    }

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    accum = (double)( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;
    
    double* res = malloc(sizeof(int));
    *res = accum;
    return (void*)res;
}

void* countB(){
    struct timespec start, stop;
    double accum;

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    printf("Process B has started.\n");
    pid_t pid = fork();
    if (pid == 0){
        linux_compiler();
    }
    else{
        wait(NULL);
    }

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    accum = (double)( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;

    double* res = malloc(sizeof(int));
    *res = accum;
    return (void*)res;
}

void* countC(){
    struct timespec start, stop;
    double accum;

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    printf("Process C has started.\n");
    pid_t pid = fork();
    if (pid == 0){
        linux_compiler();
    }
    else{
        wait(NULL);
    }

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }

    accum = (double)( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;

    double* res = malloc(sizeof(int));
    *res = accum;
    return (void*)res;
}

int main(){
    double* resA;
    double* resB;
    double* resC;
    
    resA=countA();
    resB=countB();
    resC=countC();

    printf( "Process A has ended in %lf\n", *resA );
    printf( "Process B has ended in %lf\n", *resB );
    printf( "Process C has ended in %lf\n", *resC );
}