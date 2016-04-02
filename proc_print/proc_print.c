#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/vmalloc.h>
#include<linux/seq_file.h>
#include<linux/proc_fs.h>
#include "proc_print.h"
MODULE_LICENSE("GPL");

struct list_head gProcPrintListHead;

int proc_printf(struct proc_debug *pDebug, unsigned int len, char *fmt, ...)
{
	if (pDebug->count + len > pDebug->bufferSize)	{	// buffer is not enough for next input
		char *pNewBuffer = vmalloc(pDebug->bufferSize + PAGESIZE);
		if (!pNewBuffer)
			return -1;
		memset(pNewBuffer, 0, pDebug->bufferSize + PAGESIZE);
		memcpy(pNewBuffer, pDebug->printBuffer,pDebug->count);
		vfree(pDebug->printBuffer);
		pDebug->printBuffer = pNewBuffer;
		pDebug->bufferSize += PAGESIZE;
	}
	va_list arg;
	va_start(arg, fmt);
	pDebug->count += vsnprintf(pDebug->printBuffer + pDebug->count, len, fmt, arg);
	va_end(arg);
	return 0;
}
EXPORT_SYMBOL(proc_printf);

struct proc_debug *proc_find_node_by_name(char *name)
{	
	struct proc_debug *pDebug = NULL;
	list_for_each_entry(pDebug, &gProcPrintListHead, list) {
		if (strncmp(pDebug->name, name, strlen(name)) == 0)
			return pDebug;
	}
	return NULL;
}
EXPORT_SYMBOL(proc_find_node_by_name);

struct proc_debug *INIT_PROC_PRINT(char *name)
{
	struct proc_debug *pDebug;

	pDebug = proc_find_node_by_name(name);
	if (NULL != pDebug)
		return pDebug;

	pDebug = vmalloc(sizeof(struct proc_debug));
	if (!pDebug)
		return NULL;	//allocate buffer failed
	
	memset(pDebug, 0, sizeof(struct proc_debug));	
	list_add_tail(&pDebug->list, &gProcPrintListHead);
	pDebug->proc_printf = proc_printf;
	pDebug->printBuffer = vmalloc(PAGESIZE);
	if (!pDebug->printBuffer)
		return NULL;

	pDebug->bufferSize = PAGESIZE;
	snprintf(pDebug->name, MAX_LEN, "%s", name);
	return pDebug;
}
EXPORT_SYMBOL(INIT_PROC_PRINT);

void proc_print_remove(struct proc_debug *pDebug)
{
	printk("jiaguang %d\n", __LINE__);
	list_del(&pDebug->list);
	printk("jiaguang %d\n", __LINE__);
	vfree(pDebug->printBuffer);
	printk("jiaguang %d\n", __LINE__);
	vfree(pDebug);
	printk("jiaguang %d\n", __LINE__);
	return;
}
EXPORT_SYMBOL(proc_print_remove);

void proc_print_remove_all(void)
{
	struct proc_debug *pDebug;
	list_for_each_entry(pDebug, &gProcPrintListHead, list) {
		vfree(pDebug->printBuffer);
		vfree(pDebug);
	}
}

int proc_print_show(struct seq_file *seq, void *v)
{
	struct list_head *list;
	struct proc_debug *pDebug;
	list_for_each(list, &gProcPrintListHead) {
		pDebug = list_entry(list, struct proc_debug, list);
		seq_printf(seq, "\n%s\n", pDebug->name);
		seq_printf(seq, "%s\n", pDebug->printBuffer);
		seq_putc(seq, '\n');
	}
	return 0;
}

int proc_print_open(struct inode *node, struct file *file)
{
	return single_open(file, proc_print_show, node->i_private);
}

static struct file_operations fos = {
	.owner = THIS_MODULE,
	.open = proc_print_open,
	.read = seq_read,
};

static struct proc_dir_entry *pDir;
static void proc_print_create(void)
{
	INIT_LIST_HEAD(&gProcPrintListHead);
	pDir = proc_create("proc_print", 0x644, NULL, &fos);
	if (!pDir) {
		printk("create proc_print fail\n");
	}
	return;
}


static int __init proc_print_init(void)
{
	proc_print_create();
	return 0;
}

static void __exit proc_print_exit(void)
{
	proc_print_remove_all();
	if (pDir)
		proc_remove(pDir);
	return;
}

module_init(proc_print_init);
module_exit(proc_print_exit);
