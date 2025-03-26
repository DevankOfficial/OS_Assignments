#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#define __NR_kernel_2d_memcpy 451  

long kernel_2d_memcpy_syscall(void)
{
	return syscall(__NR_kernel_2d_memcpy 451 );
}

int main(int argc, char *argv[])
{
	long res = kernel_2d_memcpy_syscall();

	if(res < 0)
	{
		perror("Syscall failed. \n");
	}
	else
	{
		printf("Syscall working Successfully.\n");
	}
	return 0;
}