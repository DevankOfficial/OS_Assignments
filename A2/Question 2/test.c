#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>
#define __NR_kernel_2d_memcpy 451 


int main(int argc, char **argv)
{
    float mat1[3][3] = { {0.1, 1.0, 1.5 }, {2.2, 3.3, 4.4 } ,{5.5, 6.6, 7.7}};
    float mat2[3][3];
 
    printf("Making syscall\n");

    long res = syscall(__NR_kernel_2d_memcpy, mat1, mat2, 3, 3);

    printf("System call returned %ld.\n", res);
    perror("Console Output");

    printf("Resultant matrix:\n");

    for(int i = 0 ; i< 3 ; i++){

        for(int j =0 ; j<3 ; j++){

            printf("%d ",matrix2[i][j]);
        }

        printf("\n");
    }

    return res;
}