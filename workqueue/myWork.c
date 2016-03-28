#include<linux/init.h>
#include<linux/module.h>
#include<linux/delay.h>
MODULE_LICENSE("GPL");

static struct workqueue_struct *wq = NULL;
static struct delayed_work delay_work;
struct student {
	struct work_struct work;
	char name[20];		//in order to pass param to function
};

void print_log(struct work_struct *pWork)
{
//	mdelay(9);
	if (pWork == &delay_work)
		printk("call delayed work\n");
	else {
		printk("call work\n");
		struct student *pStu = container_of(pWork, struct student, work);
		printk("name is %s\n", pStu->name);
	}
}

static int __init work_init(void)
{
	struct student std;
	snprintf(std.name, sizeof(std.name), "hello world");
	printk("debug >>> work init\n");
	wq = create_singlethread_workqueue("debugtest");
	INIT_WORK(&std.work, print_log);
	INIT_DELAYED_WORK(&delay_work, print_log);
	printk("call before queue_work\n");
	queue_work(wq, &std.work);
//	schedule_work(&std.work);
	queue_delayed_work(wq, &delay_work, msecs_to_jiffies(2099));
	mdelay(9);
	printk("call after queue_work\n");
	return 0;
}

static void __exit work_exit(void)
{
	printk("debug >>> work exit\n");
	destroy_workqueue(wq);
	return;
}

module_init(work_init);
module_exit(work_exit);
