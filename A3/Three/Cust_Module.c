#include <linux/kernel.h>	
#include <linux/module.h>	
#include <linux/moduleparam.h>	
#include <linux/init.h>
#include <linux/unistd.h>	
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/pid_namespace.h>

int p_id;
struct pid *pid_struct;
struct task_struct *task;
static struct proc_dir_entry *proc_write_entry;
char *proc_name="task_by_pid";

extern void *SYSCALL_TABLE[];
static int USER_ID;
module_param(USER_ID, int, 0644);

MODULE_DESCRIPTION ("Task_struct");
MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("320");

int proc_reading(char buf[],char* start[],off_t offset,int count,int *eof,void* data ){
	int len=0;
	pid_struct = find_get_pid(p_id);
	task = pid_task(pid_struct,PIDTYPE_PID);
 	len = sprintf(buf,"\nname %s\n ",task->comm);
	return len;
}

int proc_writing(struct file *file,const char *buf,int count,void *data ){
	int ret;
	char *id;
	id = (char *)kmalloc(1000*sizeof(char),GFP_KERNEL);
	printk(KERN_INFO "buf passed %s",buf);
	if(copy_from_user(id,buf,count)){
    	return -EFAULT;}
	printk(KERN_INFO "id passed %s",id);
	p_id = simple_strtoul(id,NULL,0);
	printk(KERN_INFO "pid %d ret %d",p_id,ret);
	return sizeof(buf);
}

void create_new_proc_entry(){
	proc_write_entry = create_proc_entry(proc_name,0666,NULL);
	if(!proc_write_entry){
    	printk(KERN_INFO "Error Found During Creating proc.");
    	return -ENOMEM;
	}
	proc_write_entry->proc_reading = proc_reading ;
	proc_write_entry->proc_writing = proc_writing;
	printk(KERN_INFO "proc Started");
}

void Task_struct_Found(){
  	proc_write_entry = create_proc_entry(proc_name,0666,NULL);
	if(!proc_write_entry){
    	printk(KERN_INFO "Error Found During Creating proc.");
    	return -ENOMEM;
	}
	proc_write_entry->proc_reading = proc_reading;
	proc_write_entry->proc_writing = proc_writing;
	printk(KERN_INFO "proc Started");
}

static int task_init (void){
    Task_struct_Found();
    return 0;
}

static void task_exit (void){
	printk(KERN_INFO " Inside cleanup_module\n");
    remove_proc_entry(proc_name,NULL);
}

module_init (task_init);
module_exit (task_exit);