#include<linux/module.h>
#include<linux/init.h>
#include "proc_print.h"
MODULE_LICENSE("GPL");

struct proc_debug *pDebug;
struct proc_debug *pDebug1;

static int __init test_init(void)
{
	pDebug = INIT_PROC_PRINT("testcase 01");
	pDebug1 = INIT_PROC_PRINT("testcase 02");

	pDebug->proc_printf(pDebug, strlen("test case 1\n") + 1, "test case 1\n");
	pDebug->proc_printf(pDebug, strlen("test case 1\n") + 1, "test case 1\n");
	pDebug->proc_printf(pDebug, strlen("test case 1\n") + 1, "test case 1\n");
	pDebug->proc_printf(pDebug, strlen("test case 1\n") + 1, "test case 1\n");
	pDebug->proc_printf(pDebug, strlen("test case 1\n") + 1, "test case 1\n");
	pDebug->proc_printf(pDebug, strlen("test case 1\n") + 1, "test case 1\n");
	pDebug->proc_printf(pDebug, strlen("test case 1\n") + 1, "test case 1\n");

	pDebug->proc_printf(pDebug1, strlen("test case 2\n") + 1, "test case 2\n");
	pDebug->proc_printf(pDebug1, strlen("test case 2\n") + 1, "test case 2\n");
	pDebug->proc_printf(pDebug1, strlen("test case 2\n") + 1, "test case 2\n");
	pDebug->proc_printf(pDebug1, strlen("test case 2\n") + 1, "test case 2\n");
	pDebug->proc_printf(pDebug1, strlen("test case 2\n") + 1, "test case 2\n");
}

static void __exit test_exit(void)
{
	proc_print_remove(pDebug1);
	proc_print_remove(pDebug);
	return 0;
}
module_init(test_init);
module_exit(test_exit);
