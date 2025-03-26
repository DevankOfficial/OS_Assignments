#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

int main(){
    //double a = pow((double)2,(double)32);
    double a = pow((double)2,(double)16);
    int i=0;
    for (i=0;i<a;i++){
        //printf("%d %d\n",i, x);
        printf("%d\n", i);
    }
    printf("%d\n",i);
}