#include<linux/module.h>
#include<linux/init.h>
#include<linux/timer.h>
#include<linux/wait.h>
#include<linux/workqueue.h>
#include<linux/sched.h>
MODULE_LICENSE("GPL");

struct timer_list timer;
struct workqueue_struct *wq;
struct work_struct work;
wait_queue_head_t waitQueue;
int timeoutFlag;

void thread_function(struct work_struct *work)
{
	int ret = 0;
	
	printk("begin to wait\n");
	ret = wait_event_timeout(waitQueue, timeoutFlag, 5*HZ);
	if (ret == 0)
		printk("ret = 0 timeout\n");
	else if (ret == 1)
		printk("ret = 1 condition true when timeout\n");
	else if (ret > 1)
		printk("ret > 1 condition true in %d, HZ=%d\n", ret, HZ);
	printk("wait done\n");
}



void timeout_callback(unsigned long data)
{
	printk("call timeout\n");
	timeoutFlag = 1;
	wake_up(&waitQueue);
}

static int __init wait_queue_init(void)
{
	printk("init begin\n");
	
	init_waitqueue_head(&waitQueue);

	init_timer(&timer);
	timer.expires = jiffies + 3*HZ;
	timer.function = timeout_callback;
	timer.data = 0;
	add_timer(&timer);


	wq = create_singlethread_workqueue("myThread");
	INIT_WORK(&work, thread_function);
	queue_work(wq, &work);


	printk("init end\n");
	return 0;
}

static void __exit wait_queue_exit(void)
{
	del_timer(&timer);
	destroy_workqueue(wq);
	return;
}
module_init(wait_queue_init);
module_exit(wait_queue_exit);
