#ifndef __PROC_PRINT_H__
#define  __PROC_PRINT_H__

#define MAX_LEN 50
#define PAGESIZE 4096
struct proc_debug {
	struct list_head list;
	char name[MAX_LEN];
<<<<<<< HEAD
=======
	void (*proc_printf) (struct proc_debug *debug, char *fmt, ...);
>>>>>>> 9c6b2ac6dd068616a74b3cc0ba02a3a9832406e9
	char *printBuffer;
	unsigned int bufferSize;	// total buffer size of printBuffer
	unsigned int count;			// current buffer size
};

struct proc_debug *proc_find_node_by_name(char *name);
int proc_printf(struct proc_debug *pDebug, unsigned int len, char *fmt, ...);
struct proc_debug *INIT_PROC_PRINT(char *name);
void proc_print_remove(struct proc_debug *pDebug);
#endif
