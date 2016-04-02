#include<linux/module.h>
#include<linux/init.h>
MODULE_LICENSE("GPL");

struct timer_list timer;

void time_out_function(unsigned long data)
{
	printk("call timeout %d\n", data);
}

static int __init timer_init(void)
{
	init_timer(&timer);
	timer.expires = jiffies + 4 * HZ;
	timer.data = 4;
	timer.function = time_out_function;
	printk("start timer\n");
	add_timer(&timer);
}

static void __exit timer_exit(void)
{
	del_timer(&timer);
}

module_init(timer_init);
module_exit(timer_exit);
