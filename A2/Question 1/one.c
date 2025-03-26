#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define BILLION 1000000000L
#define NO_OF_THREADS 3

void counter(){
    // double a = pow((double)2,(double)32);
    int a = pow((double)(2),(double)(32));
    int i;
    // for (i=0;i<=a;i++){
    //     //printf("%d %d\n",i, x);
    //     //printf("%d\n", i);
    // }
    printf("%d\n", a);
}

double* countA(){
    struct timespec start, stop;
    double accum;

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    printf("Thread A has started.\n");
    //execl("./Counter", "1",NULL);
    counter();

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    accum = (double)( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;
    //printf( "Process A has ended in %lf\n", accum );
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

    printf("Thread B has started.\n");
    //execl("./Counter", "2",NULL);
    counter();

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    accum = (double)( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;

    //printf( "Process B has ended in %lf\n", accum );
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

    printf("Thread C has started.\n");
    //execl("./Counter", "3",NULL);
    counter();

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    accum = (double)( stop.tv_sec - start.tv_sec )
          + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;

    //printf( "Process C has ended in %lf\n", accum );
    double* res = malloc(sizeof(int));
    *res = accum;
    return (void*)res;
}

int main(){
    const struct sched_param* param;
    //param.sched_priority = strtol(&main_sched_str[1], NULL, 0);
    pthread_t thr_A;
    pthread_t thr_B;
    pthread_t thr_C;
    //pthread_attr_t attr[NO_OF_THREADS];
    //pthread_attr_init(&attr);
    double* resA;
    double* resB;
    double* resC;
    
    pthread_create(&thr_A, NULL, (void*)countA, NULL);
    pthread_create(&thr_B, NULL, (void*)countB, NULL);
    pthread_create(&thr_C, NULL, (void*)countC, NULL);
    pthread_setschedparam(thr_A, SCHED_OTHER, param);
    pthread_setschedparam(thr_B, SCHED_RR, param);
    pthread_setschedparam(thr_C, SCHED_FIFO, param);
    pthread_join(thr_A, (void**) &resA);
    pthread_join(thr_B, (void**) &resB);
    pthread_join(thr_C, (void**) &resC);

    printf( "Thread A has ended in %lf\n", *resA );
    printf( "Thread B has ended in %lf\n", *resB );
    printf( "Thread C has ended in %lf\n", *resC );
}