#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE4(copy, float**, mat1, float**, mat2, int, row, int ,col)
{
    float two_d[row][col];

    long first = copy_from_user(two_d, mat1, row*col*sizeof(float));
   	if(first){
		return -EFAULT;
	}
    long second = copy_to_user(mat2, two_d, row*col*sizeof(float));
	
	if(second){
		return -EFAULT;
	}

    printk("Matrix copy successful!");

    return 0;
}